//
// Copyright (c) 2006 Microsoft Corporation. All rights reserved.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Management.Automation;
using System.Management.Automation.Runspaces;

namespace Microsoft.Samples.PowerShell.Runspaces
{    
    class Runspace09
    {
        /// <summary>
        /// This sample uses the Runspace and Pipeline classes to execute
        /// a script that generates the numbers from 1 to 10 with delays
        /// between each number. It uses the asynchronous capabilities of
        /// the pipeline to manage the execution of the pipeline and
        /// retrieve results as soon as they are available from a
        /// a script.
        /// </summary>
        /// <param name="args">Unused</param>
        /// <remarks>
        /// This sample demonstrates the following:
        /// 1. Creating instances of the Runspace and Pipeline classes.
        /// 2. Using these instances to execute a string as a PowerShell script.
        /// 3. Using the Pipeline InvokeAsync method and the events on the Pipeline and
        ///    output pipe classes to process script output asynchronously.
        /// 4. Using the Pipeline Stop() method to interrupt an executing pipeline.
        /// </remarks>
        static void Main(string[] args)
        {
            Console.WriteLine("Print the numbers from 1 to 10. Hit any key to halt processing\n");

            // Create a runspace. 
            // (Note that no PSHost instance is supplied in the constructor so the
            // default PSHost implementation is used. See the Hosting topics for
            // more information on creating your own PSHost class.)

            Runspace myRunSpace = RunspaceFactory.CreateRunspace();
            myRunSpace.Open();

            // Create a pipeline with a script that generates the numbers from 1 to 10. One
            // number is generated every half second.
            Pipeline pipeLine = myRunSpace.CreatePipeline("1..10 | foreach {$_ ; start-sleep -milli 500}");

            // The input pipe must be closed before running asynchronously. The pipeline
            // blocks to accumulate all input before execution begins.
            pipeLine.Input.Close();
            pipeLine.InvokeAsync();

            // Set up the event handlers for the data ready from output
            pipeLine.Output.DataReady += new EventHandler(Output_DataReady);
            // and for pipeline state changes...
            pipeLine.StateChanged += new EventHandler<PipelineStateEventArgs>(p_StateChanged);

            // Wait for things to happen. If the user hits a key before the
            // pipeline has completed, then call the pipeline Stop() method
            // to halt processing.
            Console.ReadKey();
            if (pipeLine.PipelineStateInfo.State != PipelineState.Completed)
            {
                // Stop the pipeline...
                Console.WriteLine("\nStopping the pipeline!\n");
                pipeLine.Stop();

                // Wait for the pipeline state change messages to be displayed...
                System.Threading.Thread.Sleep(500);
                Console.WriteLine("\nPress a key to exit");
                Console.ReadKey();
            }

            // Finally close the runspace to clean up any resources.
            myRunSpace.Close();
        }

        /// <summary>
        /// Output data ready event handler. This event is called when
        /// there is data available from the output pipe. It reads the
        /// data available and displays it on the console.
        /// </summary>
        /// <param name="sender">The output pipe this event is associated with.</param>
        /// <param name="e">Unused</param>
        static void Output_DataReady(object sender, EventArgs e)
        {
            PipelineReader<PSObject> myp = (PipelineReader<PSObject>)sender;

            Console.WriteLine(myp.Read().ToString());
        }

        /// <summary>
        /// This event handler is called when the pipeline state is changed.
        /// If the state change is to Completed, it issues a message
        /// asking the user to exit the program.
        /// </summary>
        /// <param name="sender">Unused</param>
        /// <param name="e">The pipeline state information.</param>
        static void p_StateChanged(object sender, PipelineStateEventArgs e)
        {
            Console.WriteLine("Pipeline state changed: state: {0}\n", e.PipelineStateInfo.State);
            if (e.PipelineStateInfo.State == PipelineState.Completed)
            {
                Console.WriteLine("Processing completed, press a key to exit!");
            }
        }
    }
}