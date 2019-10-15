//
//  basicNode.h
//  basicNode
//
//  Details: this node lets you convert a curve arc length into a u parameter
//  Example: (MEL) createNode basicNode
//
//  Created by Stephan Osterburg on 12/18/17
//
//

#ifndef basicNode_h
#define basicNode_h

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class basicNode : public MPxNode
{
public:
    // minimum required functions
    virtual MStatus     compute(const MPlug& plug, MDataBlock& data);
    static void*        creator();
    static MStatus      initialize();
    
public:
    // Node ID
    static MTypeId      typeId;
    
    // Input Value
    static MObject      inputValue;
    
    // Input Curve
    static MObject      inputCurve;
    
    //Output attribute holding the computed data
    static MObject      outputValue;
};

#endif /* basicNode_h */
