//
//  basicNode.cpp
//  basicNode
//
//  Created by Stephan Osterburg on 12/18/17
//
//
#include <basicNode.h>

#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MFloatPoint.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MPlug.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MFnCompoundAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MDataHandle.h>
#include <cmath>

MTypeId basicNode::typeId( 0x80004 );

// Attributes
MObject basicNode::inputValue;
MObject basicNode::inputCurve;
MObject basicNode::outputValue;

// Class (override - create an instance)
void* basicNode::creator()
{
    return new basicNode();
}

// initial node creation
MStatus basicNode::initialize()
{
    // Declare all the needed atrributes
    MFnNumericAttribute numFn; // -> float, double etc
    MFnTypedAttribute typedFn; // -> type of input eg curve, surface etc
    
    MStatus status;
    
    inputValue = numFn.create("inputValue", "iv", MFnNumericData::kDouble, 0 , &status);
    
    // if (status != MStatus::kSuccess)
    // do stuff
    
    numFn.setKeyable(true);
    numFn.setWritable(true);
    numFn.setStorable(true);
    addAttribute(inputValue);
    
    inputCurve = typedFn.create("inputCurve", "icrv", MFnData::kNurbsCurve);
    typedFn.setKeyable(true);
    typedFn.setWritable(true);
    typedFn.setStorable(true);
    addAttribute(inputCurve);
    
    outputValue = numFn.create("outputValue", "ov", MFnNumericData::kDouble);
    numFn.setKeyable(false);
    numFn.setStorable(false);
    numFn.setWritable(false);
    addAttribute(outputValue);
    
    attributeAffects(inputValue, outputValue);
    attributeAffects(inputCurve, outputValue);
    
    return MS::kSuccess;
}

MStatus basicNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // Make sure to trigger only when needed
    if (plug == outputValue)
    {
        // Read Input
        double inVal = dataBlock.inputValue(inputValue).asDouble();
        MObject crvVal = dataBlock.inputValue(inputCurve).asNurbsCurve();
        
        // Compute corresponding parameter
        MFnNurbsCurve crvFn(crvVal);
        double outVal = crvFn.findParamFromLength(inVal);
        
        MGlobal::displayInfo("baseNode works"); // displayInfo(MString() + inVal) to display a number as string
        
        // Set the output
        dataBlock.outputValue(outputValue).set(outVal);
        dataBlock.outputValue(outputValue).setClean();
    }
    
    return MS::kSuccess;
}













