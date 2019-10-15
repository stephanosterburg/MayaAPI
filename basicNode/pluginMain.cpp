//
//  pluginMain.cpp
//  basicNode
//
//  Created by Stephan Osterburg on 12/18/17
//
//

#include <basicNode.h>

#include <maya/MFnPlugin.h>

MStatus initializePlugin( MObject obj )
{
    MStatus stat;
    
    MFnPlugin fnPlugin(obj, "Stephan Osterburg", "0.1", "Any");
    
    stat = fnPlugin.registerNode("basicNode",
                                 basicNode::typeId,
                                 basicNode::creator,
                                 basicNode::initialize,
                                 MPxNode::kDependNode);
    
    if (stat != MS::kSuccess) {
        stat.perror("Could not register the poseReader node");
    }
    
    return stat;
}

MStatus uninitializePlugin(MObject object)
{
    MFnPlugin pluginFn;
    pluginFn.deregisterNode(MTypeId(0x80004));
    
    return MS::kSuccess;
}
