#include "octant.h"
#include "bounds.h"

Octant::Octant() {}
/**
 * Inicializa un novo octante
 * @param center Centro do octante
 * @param radius Radio do octante
 * @param startIdx Indice de inicio
 * @param endIdx Indice de fin
 * @param size Tamaño
 */
Octant::Octant(const Vector center, const double radius, const unsigned int startIdx, const unsigned int endIdx,
               const unsigned size)
        : center_(center), radius_(radius), startIdx_(startIdx), endIdx_(endIdx), size_(size) {
    bound_ = new Bound(center, radius);
    nOctants_ = 0;
}
/**
 * Borra o octante e sucesores de memoria
 */
Octant::~Octant() {
    delete bound_;
    for(size_t i = 0; i < 8; i++) {
        if(octants_[i]){
            delete octants_[i];
        }
    }
}
/**
 * Xera o código Morton dun punto
 * @param p Punto do que calcular o código
 * @return código
 */
int Octant::octantIdx(Lpoint p) {
    int child = 0;
    if (p.getX() > center_.getX())
        child |= 1;
    if (p.getY() > center_.getY())
        child |= 2;
    if (p.getZ() > center_.getZ())
        child |= 4;
    return child;
}





