#ifndef __AroundCamera_H__
#define __AroundCamera_H__

#include "Enter3D.h"

class AroundCamera : public Enter3D
{
public:
	AroundCamera() {}
	virtual ~AroundCamera() {}

public:
	virtual void render();
};


#endif //__AroundCamera_H__
