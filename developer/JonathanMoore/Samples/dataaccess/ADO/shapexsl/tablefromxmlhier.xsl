<?xml version="1.0" ?>
<!-- tablefromxmlhier.xsl -->

<!--	A somewhat generic stylesheet for transforming a table-like structured XML
	document into an HTML table.  Only extracts the first 6 columns of the first 2
	hierarchical levels.
	
	The expected input structure is of the form:

	<root-element>
		<row-element column1-name="column1-data" column2-name="column2-data" ... >
			<childrow-element childcolumn1-name="childcolumn1-data" ... />
			<childrow-element childcolumn1-name="childcolumn1-data" ... >
		</row-element>
		<row-element column1-name="column1-data" column2-name="column2-data" ... >
			<childrow-element childcolumn1-name="childcolumn1-data" ... />
			<childrow-element childcolumn1-name="childcolumn1-data" ... >
		</row-element>
		...
	</root-element>
-->

<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/TR/WD-xsl">
 
<xsl:template match="/">
      <xsl:apply-templates/>
</xsl:template>
 
<xsl:template match="/*">
<table BGCOLOR="#CCCCFF">
    <xsl:for-each select="*[0]/@*[index() $lt$ 6]">
      <th>
        <xsl:node-name/>
      </th>
    </xsl:for-each>

    <xsl:apply-templates/>
</table>

</xsl:template>

<xsl:template match="/*/*">
  <tr>
    <xsl:for-each select="@*[index() $lt$ 6]">
      <td>
        <xsl:value-of/>
      </td>
    </xsl:for-each>
  </tr>

  <xsl:for-each select="node()">
    <xsl:if test="context()[0]">
    <tr>
      <td></td>
      <xsl:for-each select="@*[index() $lt$ 6]">
      <td>
        <b><xsl:node-name/></b>
      </td>
      </xsl:for-each>
    </tr>
    </xsl:if>

    <tr>
      <td></td>
      <xsl:for-each select="@*[index() $lt$ 6]">
      <td>
        <xsl:value-of/>
      </td>
      </xsl:for-each>
    </tr>
  </xsl:for-each>
</xsl:template>


</xsl:stylesheet>
