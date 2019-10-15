#include <maya/MSimple.h>
#include <maya/MIOStream.h>
#include <maya/MGlobal.h>


DeclareSimpleCommand( helloWorld, "S Osterburg - Maya C++ Course", "Maya 2017");

MStatus helloWorld::doIt( const MArgList& )
{
    cout << "Hello World\n" << endl;

    std::cout<<"This should come from the shell\n";

    MGlobal::displayInfo("Hello Maya in the maya command shell");
    MGlobal::displayWarning("This should be a warning");
    MGlobal::displayError("This should be an error");

    return MS::kSuccess;
}
