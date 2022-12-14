//
// Copyright (c) 2006 Microsoft Corporation. All rights reserved.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//

using System;
using System.IO;
using System.Data;
using System.Data.Odbc;
using System.Management.Automation;
using System.Management.Automation.Provider;
using System.ComponentModel;

namespace Microsoft.Samples.PowerShell.Providers
{
   #region AccessDBProvider

    /// <summary>
   /// A PowerShell Provider which acts upon a access data store.
   /// </summary>
   /// <remarks>
   /// This example only demonstrates the drive overrides
   /// </remarks>
   [CmdletProvider("AccessDB", ProviderCapabilities.None)]
   public class AccessDBProvider : DriveCmdletProvider
   {
       #region Drive Manipulation

       /// <summary>
       /// Create a new drive.  Create a connection to the database file and set
       /// the Connection property in the PSDriveInfo.
       /// </summary>
       /// <param name="drive">
       /// Information describing the drive to add.
       /// </param>
       /// <returns>The added drive.</returns>
       protected override PSDriveInfo NewDrive(PSDriveInfo drive)
       {
           // check if drive object is null
           if (drive == null)
           {
               WriteError(new ErrorRecord(
                   new ArgumentNullException("drive"), 
                   "NullDrive",
                   ErrorCategory.InvalidArgument, 
                   null)
               );
            
               return null;
           }
        
           // check if drive root is not null or empty
           // and if its an existing file
           if (String.IsNullOrEmpty(drive.Root) || (File.Exists(drive.Root) == false))
           {
               WriteError(new ErrorRecord(
                   new ArgumentException("drive.Root"), 
                   "NoRoot",
                   ErrorCategory.InvalidArgument, 
                   drive)
               );
 
               return null;
           }

           // create a new drive and create an ODBC connection to the new drive
           AccessDBPSDriveInfo accessDBPSDriveInfo = new AccessDBPSDriveInfo(drive);

           OdbcConnectionStringBuilder builder = new OdbcConnectionStringBuilder();

           builder.Driver = "Microsoft Access Driver (*.mdb)";
           builder.Add("DBQ", drive.Root);
          
           OdbcConnection conn = new OdbcConnection(builder.ConnectionString);
           conn.Open();
           accessDBPSDriveInfo.Connection = conn;

           return accessDBPSDriveInfo;
       } // NewDrive

       /// <summary>
       /// Removes a drive from the provider.
       /// </summary>
       /// <param name="drive">The drive to remove.</param>
       /// <returns>The drive removed.</returns>
       protected override PSDriveInfo RemoveDrive(PSDriveInfo drive)
       {
           // check if drive object is null
           if (drive == null)
           {
               WriteError(new ErrorRecord(
                   new ArgumentNullException("drive"), 
                   "NullDrive",
                   ErrorCategory.InvalidArgument, 
                   drive)
               );

              return null;
           }

           // close ODBC connection to the drive
           AccessDBPSDriveInfo accessDBPSDriveInfo = drive as AccessDBPSDriveInfo;

           if (accessDBPSDriveInfo == null)
           {
               return null;
           }
           accessDBPSDriveInfo.Connection.Close();
         
           return accessDBPSDriveInfo;
       } // RemoveDrive

       #endregion Drive Manipulation

   } // AccessDBProvider

   #endregion AccessDBProvider

   #region AccessDBPSDriveInfo

   /// <summary>
   /// Any state associated with the drive should be held here.
   /// In this case, it's the connection to the database.
   /// </summary>
   internal class AccessDBPSDriveInfo : PSDriveInfo
   {
       private OdbcConnection connection;

       /// <summary>
       /// ODBC connection information.
       /// </summary>
       public OdbcConnection Connection
       {
           get { return connection; }
           set { connection = value; }
       }

       /// <summary>
       /// Constructor that takes one argument
       /// </summary>
       /// <param name="driveInfo">Drive provided by this provider</param>
       public AccessDBPSDriveInfo(PSDriveInfo driveInfo)
           : base(driveInfo)
       { }

   } // class AccessDBPSDriveInfo

   #endregion AccessDBPSDriveInfo

   #region PowerShell snap-in

   /// <summary>
   /// Create this sample as an PowerShell snap-in
   /// </summary>
   [RunInstaller(true)]
   public class AccessDBProviderPSSnapIn02 : PSSnapIn
   {
       /// <summary>
       /// Create an instance of the AccessDBProviderPSSnapIn02
       /// </summary>
       public AccessDBProviderPSSnapIn02()
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
               return "AccessDBProviderPSSnapIn02";
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
       /// Gets resource information for vendor. This is a string of format: 
       /// resourceBaseName,resourceName. 
       /// </summary>
       public override string VendorResource
       {
           get
           {
               return "AccessDBProviderPSSnapIn02,Microsoft";
           }
       }

       /// <summary>
       /// Description of this PowerShell snap-in.
       /// </summary>
       public override string Description
       {
           get
           {
               return "This is a PowerShell snap-in that includes the MS-Access DB PowerShell Provider .";
           }
       }
   }

   #endregion PowerShell snap-in

}

