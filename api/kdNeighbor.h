// Copyright (c) All Rights Reserved, Navié
//
// This does not touch the license for the Cinema 4D specific code functions used
// Please see the Cinema 4D license correspondingly. All other rights reserved.
//
// Author: Samir Kharchi
#ifndef KDNEIGHBOR_H
#define KDNEIGHBOR_H

#include <cmath>
#include <vector>

namespace NAVIE_GLOBAL
{
	class NeighborData
	{
	public:
		NeighborData() : index(-1), r(0.0), rr(0.0) {}
		NeighborData(int i, double _rr) : index(i), rr(_rr), r(sqrt(rr)) {}
		NeighborData(int i, double _rr, double R, double RR) : index(i), rr(_rr), r(sqrt(rr)) { }
		// Special constructor which does NOT calculate regular distance (will be set to squared distance)
		NeighborData(double _rr, int i) : index(i), rr(_rr), r(_rr) {}

		int index;
		double rr; // squared distance
		double r;  // regular distance
	};

	typedef std::vector<NAVIE_GLOBAL::NeighborData> Neighbours;

#define FOR_EACH_NEIGHBOR(n) for(NAVIE_GLOBAL::Neighbours::iterator neighbor_i = n.begin(); neighbor_i != n.end(); ++neighbor_i) {
#define FOR_EACH_CNEIGHBOR(n) for(NAVIE_GLOBAL::Neighbours::const_iterator neighbor_i = n.begin(); neighbor_i != n.end(); ++neighbor_i) {
}

#endif //KDNEIGHBOR_H