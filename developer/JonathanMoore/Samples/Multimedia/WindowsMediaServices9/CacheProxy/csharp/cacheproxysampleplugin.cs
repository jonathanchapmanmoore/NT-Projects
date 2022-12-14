//------------------------------------------------------------------------------
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// <autogenerated>
//     This code was generated by a tool.
//     Runtime Version: 1.0.3705.0
//
//     Changes to this file may cause incorrect behavior and will be lost if 
//     the code is regenerated.
// </autogenerated>
//------------------------------------------------------------------------------

// 
// This source code was auto-generated by xsd, Version=1.0.3705.0.
// 
using System.Xml.Serialization;


/// <remarks/>
[System.Xml.Serialization.XmlTypeAttribute(Namespace="http://schemas.microsoft.com/wms/2002/07/wmsCacheProxyConfigSchema")]
[System.Xml.Serialization.XmlRootAttribute(Namespace="http://schemas.microsoft.com/wms/2002/07/wmsCacheProxyConfigSchema", IsNullable=false)]
public class PersistedConfiguration {
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="normalizedString")]
    public string cacheDirectoryPath;
    
    /// <remarks/>
    public int diskQuota;
    
    /// <remarks/>
    public int archiveQuotaPerStream;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="anyURI", IsNullable=true)]
    public string reverseProxyRedirectURL;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute(DataType="normalizedString", IsNullable=true)]
    public string backendServer;
    
    /// <remarks/>
    public bool enableCaching;
    
    /// <remarks/>
    public bool enableProxy;
    
    /// <remarks/>
    public bool proxyOnDemandCacheMiss;
    
    /// <remarks/>
    public bool cacheOnDemandCacheMiss;
    
    /// <remarks/>
    public bool handleUpstreamCacheRequests;
    
    /// <remarks/>
    public protocolEnum protocol;
}

/// <remarks/>
[System.Xml.Serialization.XmlTypeAttribute(Namespace="http://schemas.microsoft.com/wms/2002/07/wmsCacheProxyConfigSchema")]
public enum protocolEnum {
    
    /// <remarks/>
    clientprotocol,
    
    /// <remarks/>
    HTTP,
    
    /// <remarks/>
    RTSPU,
    
    /// <remarks/>
    RTSPT,
}

/// <remarks/>
[System.Xml.Serialization.XmlTypeAttribute(Namespace="http://schemas.microsoft.com/wms/2002/07/wmsCacheProxyConfigSchema")]
[System.Xml.Serialization.XmlRootAttribute("PersistedConfigurationDataSet", Namespace="http://schemas.microsoft.com/wms/2002/07/wmsCacheProxyConfigSchema", IsNullable=false)]
public class PersistedConfigurationDataSet {
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("PersistedConfiguration")]
    public PersistedConfiguration[] Items;
}
