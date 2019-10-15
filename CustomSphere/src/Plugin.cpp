#include "CustomSphere.h"
#include <maya/MFnPlugin.h>


MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, "", "S Osterburg - Maya C++ course" , "Maya 2017" );

	status = plugin.registerCommand( "customCreateSphere", CustomSphere::creator );

	if ( !status )
	{
        status.perror( "Unable to register command \"customCreateSphere\"" );
		return status;
	}

	return status;
}


MStatus uninitializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj );

    status = plugin.deregisterCommand( "customCreateSphere" );

	if ( !status )
	{
        status.perror( "Unable to register command \"customCreateSphere\"" );
		return status;
	}

	return status;
}

