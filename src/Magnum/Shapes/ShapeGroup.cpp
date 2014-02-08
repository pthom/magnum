/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "ShapeGroup.h"

#include "Magnum/Shapes/AbstractShape.h"

namespace Magnum { namespace Shapes {

template<UnsignedInt dimensions> void ShapeGroup<dimensions>::setClean() {
    /* Clean all objects */
    if(!this->isEmpty()) {
        std::vector<std::reference_wrapper<SceneGraph::AbstractObject<dimensions, Float>>> objects;
        objects.reserve(this->size());
        for(std::size_t i = 0; i != this->size(); ++i)
            objects.push_back((*this)[i].object());

        SceneGraph::AbstractObject<dimensions, Float>::setClean(objects);
    }

    dirty = false;
}

template<UnsignedInt dimensions> AbstractShape<dimensions>* ShapeGroup<dimensions>::firstCollision(const AbstractShape<dimensions>& shape) {
    setClean();
    for(std::size_t i = 0; i != this->size(); ++i)
        if(&(*this)[i] != &shape && (*this)[i].collides(shape))
            return &(*this)[i];

    return nullptr;
}

#ifndef DOXYGEN_GENERATING_OUTPUT
template class MAGNUM_SHAPES_EXPORT ShapeGroup<2>;
template class MAGNUM_SHAPES_EXPORT ShapeGroup<3>;
#endif

}}
