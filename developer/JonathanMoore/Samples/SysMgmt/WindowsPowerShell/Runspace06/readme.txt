Runspace Sample 06
==========================
     This sample introduces how to add a PSSnapin to RunspaceConfiguration 
     and then use modified RunspaceConfiguration to create the Runspace.

Sample Language Implementations
===============================
     This sample is available in the following language implementations:

     - C#


To build the sample using Visual Studio:
=======================================
     1. Open Windows Explorer and navigate to Runspace06 under the samples directory.
     2. Double-click the icon for the .sln (solution) file to open the file in Visual Studio.
     3. In the Build menu, select Build Solution.
     The library will be built in the default \bin or \bin\Debug directory.

To run the sample:
=================
     1. Start command prompt.
     2. Navigate to the folder containing the sample executable.
     3. Run the executable

Demonstrates
============
     This sample demonstrates the following:

     1. Creating an instance of RunspaceConfiguration
     2. Adding a PowerShell snap-in to this configuration
     3. Using the configuration to create a runspace
     4. Create a pipeline with the get-proc cmdlet available in the PowerShell snap-in
     5. Using PSObject to extract and display properties from the objects
        returned by this command