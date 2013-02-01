/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2011, Rice University
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Rice University nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Matt Maly */

#ifndef OMPL_CONTROL_PLANNERS_SYCLOP_GRIDDECOMPOSITION_
#define OMPL_CONTROL_PLANNERS_SYCLOP_GRIDDECOMPOSITION_

#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include "ompl/base/spaces/RealVectorBounds.h"
#include "ompl/base/State.h"
#include "ompl/control/planners/syclop/Decomposition.h"

namespace ompl
{
    namespace control
    {
        /** \brief A GridDecomposition is a Decomposition implemented using a grid. */
        class GridDecomposition : public Decomposition
        {
        public:
            /** \brief Constructor. Creates a GridDecomposition as a hypercube with a given dimension, side length, and bounds. */
            GridDecomposition(const int len, const std::size_t dim, const base::RealVectorBounds& b);

            virtual ~GridDecomposition()
            {
            }

            virtual double getRegionVolume(const int rid) const
            {
                return cellVolume_;
            }

            virtual void getNeighbors(const int rid, std::vector<int>& neighbors) const;

            virtual int locateRegion(const base::State* s) const;

            virtual const base::RealVectorBounds& getRegionBounds(const int rid);

        protected:
            /** \brief Converts a given region to a coordinate in the grid. */
            void regionToCoord(int rid, std::vector<int>& coord) const;

            /** \brief Converts the given coordinate to the region in the grid. */
            int coordToRegion (const std::vector<int> &coord) const;

            /** \brief Computes the neighbors of the given region in a n-dimensional grid */
            void computeGridNeighbors (int rid, std::vector <int> &neighbors) const;

            /** Recursive subroutine for grid neighbor computation */
            void computeGridNeighborsSub (const std::vector <int>&coord, std::vector <int> &neighbors,
                                          unsigned int dim, std::vector <int> &candidate) const;

            const int length_;
            double cellVolume_;
            boost::unordered_map<int, boost::shared_ptr<base::RealVectorBounds> > regToBounds_;

        private:
            /** \brief Helper method to return len^dim in call to super-constructor. */
            int calcNumRegions(const int len, const std::size_t dim) const;
        };
    }
}
#endif
