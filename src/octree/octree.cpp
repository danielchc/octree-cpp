#include "octree.h"
#include "Kernel.h"


/**
 * Inicializa un octree sen puntos
 * @param max_bucket Tamaño máximo de puntos nas follas
 */
Octree::Octree(unsigned int max_bucket) : max_bucket_(max_bucket) {}

Octree::Octree(std::vector<Lpoint> &points, unsigned int max_bucket) : max_bucket_(max_bucket) {
	Vector center;
	double radius;
	numPoints_ = points.size();
	points_.reserve(numPoints_);
	successors_.reserve(numPoints_);
	insertPoints(points);
	center = mbb(points, radius);
	buildOctree(center, radius);
}

/**
 * Borra o octree
 */
Octree::~Octree() {
	if(root_) delete root_;
}

/**
 * Inserta un array de puntos no octree
 * @param points
 */
void Octree::insertPoints(std::vector<Lpoint> &points) {
	int index=0;
	for (Lpoint &p : points) {
		points_.emplace_back(&p);
		successors_[index] = index + 1;
		index++;
	}
}

/**
 * Xera o nodo central do octree e os seus descendentes
 * @param center Centro do octree
 * @param radius Radio do octree
 */
void Octree::buildOctree(Vector center, double radius) {
	root_ = createOctant(center, radius, 0, numPoints_ - 1, numPoints_);
}

/**
 * Crea un octante
 * @param center Centro do octante
 * @param radius Radio do octante
 * @param startIdx Indice de inicio
 * @param endIdx Indice de fin
 * @param size Tamaño
 * @return
 */

Octant *
Octree::createOctant(Vector center, double radius, unsigned int startIdx, unsigned int endIdx, unsigned int size) {
	unsigned int idx = startIdx, lastIdx = 0, mortonCode = 0;
	Vector newCenter;


	Octant *octant = new Octant(center, radius, startIdx, endIdx, size);

    //Se o tamaño é inferior o tamaño do bucket é unha folla
	if (size <= max_bucket_) {
		return octant;
	}


	std::array<unsigned int, 8> childStarts = {0};
	std::array<unsigned int, 8> childEnds = {0};
	std::array<unsigned int, 8> childSizes = {0};

    //Para cada punto actualizo o seus sucesores
	Lpoint* p;
	for (unsigned int i = 0; i < size; i++) {
		p = points_[idx];
        //Calculo o código morton
		mortonCode = octant->octantIdx(*p);

		if (childSizes[mortonCode] == 0) {
			childStarts[mortonCode] = idx;
		} else {
			successors_[childEnds[mortonCode]] = idx;
		}

        //Actualizo o tamaño e o final de cada octante fillo
		childSizes[mortonCode]++;
		childEnds[mortonCode] = idx;

		idx = successors_[idx];
	}

	double newRadius = 0.5f * radius;

	for (int i = 0; i < 8; i++) {
        //Se non existe puntos ignoro
		if (childSizes[i] == 0) continue;

        //Calculo o novo centro
		newCenter.setX(octant->getCenter().getX() + (i & 1 ? 0.5f : -0.5f) * radius);
		newCenter.setY(octant->getCenter().getY() + (i & 2 ? 0.5f : -0.5f) * radius);
		newCenter.setZ(octant->getCenter().getZ() + (i & 4 ? 0.5f : -0.5f) * radius);

        //Engado o fillo o octante pai
		octant->setOctant(i, createOctant(newCenter, newRadius, childStarts[i], childEnds[i], childSizes[i]));

        //Establezco o indice de inicio do octante pai o indice do primeiro fillo
        if (octant->getOctantCount() == 0) {
            octant->setStartIdx(octant->getOctant(i)->getStartIdx());
        //Actualizo a posición o último indice do último octante creado como o primeiro do que estou a xerarl
        } else {
			successors_[octant->getOctant(lastIdx)->getEndIdx()] = octant->getOctant(i)->getStartIdx();
		}

		lastIdx = i;
        //Actualizo o último indice como o indice do último octante creado e aumento o número de octantes
		octant->setEndIdx(octant->getOctant(i)->getEndIdx());
		octant->incrementOctantCount();
	}

	return octant;
}

/**
 * Imprimo un octree nun ficheiro
 * @param f Ficheiro onde escribir
 * @param index Nivel no que empezar, por defecto 0
 */
void Octree::writeOctree(std::ofstream &f, size_t index) const {
    writeOctree(root_, f, index);
}

/**
 * Busco os puntos veciños dun punto dado
 * @param p Punto do que buscar veciños
 * @param radius Radio de busca
 * @param k_t Tipo de kernel
 * @return Vector cos veciños dun punto
 */
std::vector<Lpoint *>
Octree::searchNeighbors(const Point &p, double radius, const Kernel_t &k_t) const {
	std::vector<Lpoint *> ptsInside{};
    //Creo un kernel de busqueda
	std::unique_ptr<AbstractKernel> kernel = kernelFactory(p, radius, k_t);
    //Realizo a busca dos veciños
	neighbors(root_, kernel, ptsInside);
	return std::move(ptsInside);
}


void Octree::neighbors(Octant *octant, std::unique_ptr<AbstractKernel> &k, std::vector<Lpoint *> &ptsInside) const {
	int current;
	Lpoint* ptr;

    //Se o octante se atopa contido no kernel, meto todos os puntos do octante no resultado
	if (k->contains(*octant)) {
		current = octant->getStartIdx();
		for (int i = 0; i < octant->getSize(); i++) {
			ptr = points_[current];
			if (k->center.id() != ptr->id()) {
				ptsInside.emplace_back(ptr);
			}
			current = successors_[current];
		}
		return;
	}

    //Se é un octante folla comprobo se os puntos do octante están no kernel, e se o están engadoos o resultado
	if (octant->isLeaf()) {
		current = octant->getStartIdx();
		for (int i = 0; i < octant->getSize(); i++) {
			ptr = points_[current];
			if (k->isInside(*ptr) && k->center.id() != ptr->id()) {
				ptsInside.emplace_back(ptr);
			}
			current = successors_[current];
		}
		return;
	}

    //Se non é unha folla, descendo pola arbore se o kernel se superpon co octante
	for (Octant *child: octant->getOctants()) {
		if (child && k->boxOverlap(*child)) {
			neighbors(child, k, ptsInside);
		}
	}

}


void Octree::writeOctree(const Octant *octant, std::ofstream &f, size_t index) const {
	uint current=0;
	index++;
	for (int i = 0; i < index; i++) f << "\t";
	f
			<< "Depth: " << index << " "
			<< "numPoints: " << octant->getSize()
			<< " Center: " << octant->getCenter() << " Radius: " << octant->getRadius() << "\n";


	if (octant->isLeaf()) {
		current = octant->getStartIdx();
		for (int i = 0; i < octant->getSize(); i++) {
			for (int i = 0; i <= index; i++) f << "\t";
			f << points_[current] << "\n";
			current = successors_[current];
		}
		return;
	}

	for (const auto &oct: octant->getOctants()) {
		if (oct){
			writeOctree(oct, f, index);
		}
	}
}