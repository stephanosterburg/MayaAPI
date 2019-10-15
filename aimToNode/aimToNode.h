//
//  aimToNode.h
//  aimToNode
//
//  Details: aim to node
//  Example: (MEL) createNode aimToNode
//
//  Created by Stephan Osterburg on 12/19/17
//
//

#ifndef aimToNode_h
#define aimToNode_h

#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class aimToNode : public MPxNode
{
public:
    virtual MStatus     compute(const MPlug& plug, MDataBlock& data);
    static void*        creator();
    static MStatus      initialize();
    
public:
    // Node ID
    static MTypeId      typeId;
    
    // input matrix of constraint driver
    static MObject      upAxis;
    
    // input matrix of constraint driver
    static MObject      driverMatrix;
    
    // input matrix of contraint up vector
    static MObject      upVectorMatrix;
    
    // input translate array
    static MObject      inputTranslate;
    
    // input translate X component
    static MObject      inputTranslateX;
    
    // input translate Y component
    static MObject      inputTranslateY;
    
    // input translate Z component
    static MObject      inputTranslateZ;
    
    // output rotation array
    static MObject      outputRotate;
    
    // output rotation X component
    static MObject      outputRotateX;
    
    // output rotation Y component
    static MObject      outputRotateY;
    
    // output rotation Z component
    static MObject      outputRotateZ;
};

#endif /* aimToNode_h */
