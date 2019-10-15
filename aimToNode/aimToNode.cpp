//
//  aimToNode.cpp
//  aimToNode
//
//  Created by Stephan Osterburg on 12/19/17
//
//
#include <aimToNode.h>

#include <maya/MGlobal.h>
#include <maya/MPxTransform.h>
#include <maya/MPxTransformationMatrix.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFloatVector.h>
#include <maya/MDataHandle.h>
#include <maya/MEulerRotation.h>
#include <maya/MMatrix.h>
#include <maya/MPoint.h>
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <math.h>
#include <maya/MString.h>

MTypeId aimToNode::typeId( 0x80123 );

// Declare all attributes
MObject aimToNode::upAxis;
MObject aimToNode::driverMatrix;
MObject aimToNode::upVectorMatrix;
MObject aimToNode::inputTranslate;
MObject aimToNode::inputTranslateX;
MObject aimToNode::inputTranslateY;
MObject aimToNode::inputTranslateZ;
MObject aimToNode::outputRotate;
MObject aimToNode::outputRotateX;
MObject aimToNode::outputRotateY;
MObject aimToNode::outputRotateZ;


MMatrix setRotationMatrix(MVector vec1, MVector vec2, MVector vec3, MVector trs)
{
    // build rotation matrix
    double tempMatrix[4][4] = {
        {vec1.x, vec1.y, vec1.z, 0},
        {vec2.x, vec2.y, vec2.z, 0},
        {vec3.x, vec3.y, vec3.z, 0},
        {trs[0], trs[1], trs[2], 1}};
    
    printf("testing");
    
    return tempMatrix;
}

// Class (override - create an instance)
void* aimToNode::creator()
{
    return new aimToNode();
}

// initial node creation
MStatus aimToNode::initialize()
{
    // Declare all the needed attributes
    MFnEnumAttribute        eAttr;
    MFnMatrixAttribute      matrixFn;
    MFnNumericAttribute     numFn;
    MFnCompoundAttribute    compound;
    MFnTypedAttribute       typedFn;
    MFnUnitAttribute        uAttr;
    
    // Flag
    upAxis = eAttr.create("upAxis", "upx", 0);
    eAttr.setKeyable(true);
    eAttr.setStorable(true);
    eAttr.addField("X", 0);
    eAttr.addField("Y", 1);
    eAttr.addField("Z", 2);
    addAttribute(upAxis);
    
    // Input
    driverMatrix = matrixFn.create("driverMatrix", "drvm");
    addAttribute(driverMatrix);
    
    upVectorMatrix = matrixFn.create("upVectorMatrix", "uvcm");
    addAttribute(upVectorMatrix);
    
    inputTranslateX = numFn.create("inputTranslateX", "itx", MFnNumericData::kDouble, 0);
    numFn.setKeyable(true);
    numFn.setStorable(true);
    numFn.setWritable(true);
    addAttribute(inputTranslateX);
    
    inputTranslateY = numFn.create("inputTranslateY", "ity", MFnNumericData::kDouble, 0);
    numFn.setKeyable(true);
    numFn.setStorable(true);
    numFn.setWritable(true);
    addAttribute(inputTranslateY);
    
    inputTranslateZ = numFn.create("inputTranslateZ", "itz", MFnNumericData::kDouble, 0);
    numFn.setKeyable(true);
    numFn.setStorable(true);
    numFn.setWritable(true);
    addAttribute(inputTranslateZ);
    
    inputTranslate = compound.create("inputTranslate", "itrs");
    compound.addChild(inputTranslateX);
    compound.addChild(inputTranslateY);
    compound.addChild(inputTranslateZ);
    compound.setKeyable(true);
    compound.setStorable(true);
    compound.setWritable(true);
    addAttribute(inputTranslate);
    
    // Output
    outputRotateX = uAttr.create("outputRotateX", "orx", MFnUnitAttribute::kAngle, 0.0);
    numFn.setKeyable(false);
    numFn.setStorable(false);
    numFn.setWritable(false);
    addAttribute(outputRotateX);
    
    outputRotateY = uAttr.create("outputRotateY", "ory", MFnUnitAttribute::kAngle, 0.0);
    numFn.setKeyable(false);
    numFn.setStorable(false);
    numFn.setWritable(false);
    addAttribute(outputRotateY);
    
    outputRotateZ = uAttr.create("outputRotateZ", "orz", MFnUnitAttribute::kAngle, 0.0);
    numFn.setKeyable(false);
    numFn.setStorable(false);
    numFn.setWritable(false);
    addAttribute(outputRotateZ);
    
    outputRotate = compound.create("outputRotate", "orot");
    compound.addChild(outputRotateX);
    compound.addChild(outputRotateY);
    compound.addChild(outputRotateZ);
    compound.setKeyable(false);
    compound.setStorable(false);
    compound.setWritable(false);
    addAttribute(outputRotate);
    
    // Link attrs
    attributeAffects(inputTranslate, outputRotate);
    attributeAffects(driverMatrix, outputRotate);
    attributeAffects(upVectorMatrix, outputRotate);
    
    // Return
    return MS::kSuccess;
}

MStatus aimToNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    if ((plug == outputRotate) || (plug == outputRotateX) || (plug == outputRotateY) || (plug == outputRotateZ))
    {
        // Get flag
        MDataHandle upAxisHdl = dataBlock.inputValue(upAxis);
        int upAxisInt = upAxisHdl.asShort();
        
        //MString upAxisStrg = &upAxisHdl.asChar();
        //MGlobal::displayInfo(upAxisStrg);
        
        MString str;
        str = int(upAxisInt);
        MGlobal::displayInfo("we are in here not somewhere else");
        
        // extract input data
        MMatrix driverMatrixValue   = dataBlock.inputValue(driverMatrix).asMatrix();
        MMatrix upVectorMatrixValue = dataBlock.inputValue(upVectorMatrix).asMatrix();
        
        MVector inputTranslateValue = dataBlock.inputValue(inputTranslate).asVector();
        
        // extract driver and upvector positions
        MVector driverMatrixPos(driverMatrixValue[3][0], driverMatrixValue[3][1], driverMatrixValue[3][2]);
        MVector upVectorMatrixPos(upVectorMatrixValue[3][0], upVectorMatrixValue[3][1], upVectorMatrixValue[3][2]);
        
        // compute vectors
        MVector upVector  = upVectorMatrixPos - inputTranslateValue;
        MVector aimVector = driverMatrixPos - inputTranslateValue;
        upVector.normalize();
        aimVector.normalize();
        
        // compute perpendicular vector
        // ^ is the cross product operator
        MVector cross = aimVector ^ upVector; // first calc the cross product
        upVector = cross ^ aimVector; // second calc the new perpendicular upVector
        
        // build rotaion matrix
        MMatrix rotMatrix;
        
        if (upAxisInt == 0) {
            rotMatrix = setRotationMatrix(aimVector, upVector, cross, inputTranslateValue);
        } else if (upAxisInt == 1) {
            rotMatrix = setRotationMatrix(upVector, aimVector, cross, inputTranslateValue);
        } else if (upAxisInt == 2) {
            rotMatrix = setRotationMatrix(aimVector, cross, upVector, inputTranslateValue);
        }
        
        
        //double tempMatrix[4][4] = {
        //    {aimVector.x, aimVector.y, aimVector.z, 0},
        //    {upVector.x,  upVector.y,  upVector.z,  0},
        //    {cross.x,     cross.y,     cross.z,     0},
        //    {inputTranslateValue[0], inputTranslateValue[1], inputTranslateValue[2], 1}};
        
        // extract euler rotation
        //MMatrix rotMatrix(tempMatrix);
        
        MTransformationMatrix matrixFn(rotMatrix);
        MEulerRotation euler = matrixFn.eulerRotation();
        
        // set output data
        dataBlock.outputValue(outputRotate).set(euler.x, euler.y, euler.z);
        dataBlock.outputValue(outputRotate).setClean();
    }
    
    return MS::kSuccess;
}












