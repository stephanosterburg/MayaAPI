//
//  pluginMain.cpp
//  aimToNode
//
//  Created by Stephan Osterburg on 12/19/17
//
//

#include <aimToNode.h>

#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;
    
    MFnPlugin fnPlugin(obj, "Stephan Osterburg", "0.1", "Any");
    
    stat = fnPlugin.registerNode("aimToNode",
                                 aimToNode::typeId,
                                 aimToNode::creator,
                                 aimToNode::initialize,
                                 MPxNode::kDependNode);
    
    if (stat != MS::kSuccess) {
        stat.perror("Could not register the poseReader node");
    }
    
    return stat;
}

MStatus uninitializePlugin(MObject object)
{
    MFnPlugin pluginFn;
    pluginFn.deregisterNode(MTypeId(0x80123));
    
    return MS::kSuccess;
}
