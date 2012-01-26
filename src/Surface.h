/*
 * Surface.h
 *
 *  Created on: Jan 9, 2012
 *      Author: wbinventor
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <vector>
#include <sstream>
#include "Point.h"
#include "Track.h"

#include "log.h"

/* Define for compiler */
class Plane;

/**
 * Surface types
 */
enum surfaceType {
	PLANE,
	CIRCLE,
	XPLANE,
	YPLANE,
	QUADRATIC
};

/**
 * Represents a 2-dimensional quadratics surface
 */
class Surface {
protected:
	static int _n;				/* Counts the number of surfaces */
	int _uid;					/* monotonically increasing id based on n */
	int _id;
	surfaceType _type;
	std::vector<int> _neighbor_pos;
	std::vector<int> _neighbor_neg;
public:
	Surface(const int id, const surfaceType type);
	virtual ~Surface();
	int getUid() const;
	int getId() const;
	surfaceType getType() const;
	std::vector<int> getNeighborPos();
	std::vector<int> getNeighborNeg();
	void setNeighborPosSize(int size);
	void setNeighborNegSize(int size);
	void setNeighborPos(int index, int cell);
	void setNeighborNeg(int index, int cell);
	virtual double evaluate(const Point* point) const =0;
	virtual int intersection(Track* track, Point* points) const =0;
	virtual int intersection(Plane* plane, Point* points) const =0;
	virtual const char* toString() =0;
};

/**
 * Represents a plane in 2D as a Surface subclass
 */
class Plane: public Surface {
private:
	double _A, _B, _C;
	friend class Surface;
	friend class Circle;
public:
	Plane(const int id, const double A, const double B, const double C);
	double evaluate(const Point* point) const;
	int intersection(Track* track, Point* points) const;
	int intersection(Plane* plane, Point* points) const;
	const char* toString();
};

/**
 * Represents a plane parallel to the x-axis as a Plane subclass
 */
class XPlane: public Plane {
private:
	double _A, _B, _C;
public:
	XPlane(const int id, const double C);
	const char* toString();
};

/**
 * Represents a plane parallel to the y-axis as a Plane subclass
 */
class YPlane: public Plane {
private:
	double _A, _B, _C;
public:
	YPlane(const int id, const double C);
	const char* toString();
};

/**
 * Represents a circle as a Surface subclass
 */
class Circle: public Surface {
private:
	Point center;
	double _radius;
	double _A, _B, _C, _D, _E;
	friend class Surface;
	friend class Plane;
public:
	Circle(const int id, const double x, const double y, const double radius);
	double evaluate(const Point* point) const;
	int intersection(Track* track, Point* points) const;
	int intersection(Plane* plane, Point* points) const;
	const char* toString();
};

#endif /* SURFACE_H_ */
