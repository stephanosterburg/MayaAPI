#include "CubeLocatorNode.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, "", "S Osterburg - Maya C++ course" , "Maya 2017" );

    // register our nodes and the commands which will be called
	status = plugin.registerNode( "cubeLocator",
                                  CubeLocatorNode::m_id,
                                  &CubeLocatorNode::creator,
								  &CubeLocatorNode::initialize,
                                  MPxNode::kLocatorNode );

	if (!status)
	{
		status.perror("Unable to register CubeLocatorNode" );
		return status;
	}


	return status;
}


MStatus uninitializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( CubeLocatorNode::m_id );

	if (!status)
	{
		status.perror( "unable to deregister CubeLocatorNode" );
		return status;
	}

	return status;
}


