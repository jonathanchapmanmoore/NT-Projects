//
// Copyright (c) 2006 Microsoft Corporation. All rights reserved.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.


// Description: PSSnapIn installation information SelectObjSnapIn

// System namespaces needed
using System.ComponentModel;

// Windows PowerShell namespaces needed
using System.Management.Automation;

namespace Microsoft.Samples.PowerShell.Commands
{
    /// <summary>
    /// Create this sample as an PowerShell snap-in
    /// </summary>
    [RunInstaller(true)]
    public class SelectObjPSSnapIn : PSSnapIn
    {
        /// <summary>
        /// Create an instance of the SelectObjPSSnapIn
        /// </summary>
        public SelectObjPSSnapIn()
            : base()
        {
        }

        /// <summary>
        /// Get a name for this PowerShell snap-in. This name will be used in registering
        /// this PowerShell snap-in.
        /// </summary>
        public override string Name
        {
            get
            {
                return "SelectObjSample";
            }
        }

        /// <summary>
        /// Vendor information for this PowerShell snap-in.
        /// </summary>
        public override string Vendor
        {
            get
            {
                return "Microsoft";
            }
        }

        /// <summary>
        /// Description of this PowerShell snap-in.
        /// </summary>
        public override string Description
        {
            get
            {
                return "This is a PowerShell snap-in that includes the select-obj cmdlet.";
            }
        }
    }
}

