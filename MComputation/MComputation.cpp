#include <maya/MSimple.h>
#include <maya/MIOStream.h>
#include <maya/MGlobal.h>
#include <maya/MComputation.h>


DeclareSimpleCommand( MComputationTest , "S Osterburg - Maya C++ course", "Maya 2017");

MStatus MComputationTest::doIt( const MArgList& )
{
    // create an MComputation class for heavy calculation type things
    MComputation Interupter;

    // set the start of the heavy computation
    Interupter.beginComputation();

    while(1)
    {
        MGlobal::displayInfo("doing a computation press ESC to stop");

        // HACK - just a little sleep loop so we don't thrash things too much
        for(int i=0; i<99999999; ++i){;}

        if( Interupter.isInterruptRequested() )
        {
            Interupter.endComputation();
            MGlobal::displayInfo("intrupted by escape");
            return MS::kFailure;
        }
    }
}

