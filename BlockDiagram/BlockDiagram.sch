<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="BlockDiagramBlocks">
<packages>
<package name="MICROCONTROLLER_BOARD">
<pad name="P$1" x="-5.08" y="2.54" drill="0.8"/>
<pad name="P$2" x="-2.54" y="2.54" drill="0.8"/>
<pad name="P$3" x="0" y="2.54" drill="0.8"/>
<pad name="P$4" x="2.54" y="2.54" drill="0.8"/>
<pad name="P$5" x="5.08" y="2.54" drill="0.8"/>
<pad name="P$6" x="7.62" y="2.54" drill="0.8"/>
<pad name="P$7" x="-5.08" y="-2.54" drill="0.8"/>
<pad name="P$8" x="-2.54" y="-2.54" drill="0.8"/>
<pad name="P$9" x="0" y="-2.54" drill="0.8"/>
<pad name="P$10" x="2.54" y="-2.54" drill="0.8"/>
<pad name="P$11" x="5.08" y="-2.54" drill="0.8"/>
<pad name="P$12" x="7.62" y="-2.54" drill="0.8"/>
<pad name="P$13" x="-7.62" y="-2.54" drill="0.8"/>
<pad name="P$14" x="-7.62" y="2.54" drill="0.8"/>
<pad name="P$16" x="-10.16" y="-2.54" drill="0.8"/>
<pad name="P$15" x="-10.16" y="2.54" drill="0.8"/>
<pad name="P$17" x="10.16" y="2.54" drill="0.8"/>
</package>
<package name="LASER_CONTROLLER_BOARD">
<pad name="P$1" x="0" y="2.54" drill="0.8"/>
<pad name="P$2" x="2.54" y="2.54" drill="0.8"/>
<pad name="P$3" x="-2.54" y="2.54" drill="0.8"/>
<pad name="P$4" x="-2.54" y="-1.27" drill="0.8"/>
<pad name="P$5" x="0" y="-1.27" drill="0.8"/>
</package>
<package name="MOTOR_CONTROLLER_BOARD">
<pad name="P$1" x="0" y="2.54" drill="0.8"/>
<pad name="P$2" x="-2.54" y="2.54" drill="0.8"/>
<pad name="P$3" x="-5.08" y="2.54" drill="0.8"/>
<pad name="P$4" x="2.54" y="2.54" drill="0.8"/>
<pad name="P$5" x="5.08" y="2.54" drill="0.8"/>
<pad name="P$6" x="7.62" y="2.54" drill="0.8"/>
<pad name="P$7" x="7.62" y="-2.54" drill="0.8"/>
<pad name="P$8" x="5.08" y="-2.54" drill="0.8"/>
<pad name="P$9" x="2.54" y="-2.54" drill="0.8"/>
<pad name="P$10" x="0" y="-2.54" drill="0.8"/>
<pad name="P$11" x="-2.54" y="-2.54" drill="0.8"/>
<pad name="P$12" x="-5.08" y="-2.54" drill="0.8"/>
</package>
</packages>
<symbols>
<symbol name="MICROCONTROLLER_BOARD">
<text x="-10.16" y="20.32" size="1.778" layer="94">Micrcontroller Board</text>
<pin name="LSR_EN" x="27.94" y="15.24" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="+3V3@1" x="-27.94" y="15.24" visible="pin" length="middle" direction="in"/>
<pin name="+12V@1" x="-27.94" y="12.7" visible="pin" length="middle" direction="in"/>
<pin name="TILT" x="-27.94" y="7.62" visible="pin" length="middle" direction="in"/>
<pin name="GND@1" x="-27.94" y="10.16" visible="pin" length="middle" direction="in"/>
<pin name="+12V@2" x="27.94" y="10.16" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="GND@2" x="27.94" y="7.62" visible="pin" length="middle" direction="in" rot="R180"/>
<pin name="+3V3@2" x="27.94" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="SPI_CS" x="27.94" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="BSY_X" x="-27.94" y="5.08" visible="pin" length="middle"/>
<pin name="SPI_MOSI" x="27.94" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="BSY_Y" x="-27.94" y="2.54" visible="pin" length="middle"/>
<pin name="SPI_CLK" x="27.94" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="FLAG_X" x="-27.94" y="0" visible="pin" length="middle"/>
<pin name="SPI_MISO" x="-27.94" y="-5.08" visible="pin" length="middle"/>
<pin name="FLAG_Y" x="-27.94" y="-2.54" visible="pin" length="middle"/>
<pin name="STNBY_RST" x="27.94" y="-2.54" visible="pin" length="middle" rot="R180"/>
<wire x1="-22.86" y1="22.86" x2="-22.86" y2="-17.78" width="0.254" layer="94"/>
<wire x1="-22.86" y1="-17.78" x2="22.86" y2="-17.78" width="0.254" layer="94"/>
<wire x1="22.86" y1="-17.78" x2="22.86" y2="22.86" width="0.254" layer="94"/>
<wire x1="22.86" y1="22.86" x2="-22.86" y2="22.86" width="0.254" layer="94"/>
</symbol>
<symbol name="LASER_CONTROLLER_BOARD">
<wire x1="-17.78" y1="15.24" x2="-17.78" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-10.16" x2="17.78" y2="-10.16" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="17.78" y2="15.24" width="0.254" layer="94"/>
<wire x1="17.78" y1="15.24" x2="-17.78" y2="15.24" width="0.254" layer="94"/>
<text x="-10.16" y="12.7" size="1.778" layer="94">Laser Controller Board</text>
<pin name="LSR_EN" x="-22.86" y="10.16" visible="pin" length="middle" direction="in"/>
<pin name="+3V3" x="22.86" y="10.16" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="+12V" x="22.86" y="7.62" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="GND" x="22.86" y="5.08" visible="pin" length="middle" direction="out" rot="R180"/>
<pin name="TILT" x="22.86" y="2.54" visible="pin" length="middle" direction="out" rot="R180"/>
</symbol>
<symbol name="MOTOR_CONTROLLER_BOARD">
<wire x1="-17.78" y1="15.24" x2="-17.78" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-12.7" x2="17.78" y2="-12.7" width="0.254" layer="94"/>
<wire x1="17.78" y1="-12.7" x2="17.78" y2="15.24" width="0.254" layer="94"/>
<wire x1="17.78" y1="15.24" x2="-17.78" y2="15.24" width="0.254" layer="94"/>
<pin name="+3V3" x="-22.86" y="7.62" visible="pin" length="middle"/>
<pin name="+12V" x="-22.86" y="5.08" visible="pin" length="middle"/>
<pin name="GND" x="-22.86" y="2.54" visible="pin" length="middle"/>
<pin name="SPI_CS" x="-22.86" y="0" visible="pin" length="middle"/>
<pin name="SPI_MOSI" x="-22.86" y="-2.54" visible="pin" length="middle"/>
<pin name="SPI_CLK" x="-22.86" y="-5.08" visible="pin" length="middle"/>
<pin name="STNBY_RST" x="-22.86" y="-7.62" visible="pin" length="middle"/>
<pin name="BSY_X" x="22.86" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="BSY_Y" x="22.86" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="FLAG_X" x="22.86" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="FLAG_Y" x="22.86" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="SPI_MISO" x="22.86" y="-2.54" visible="pin" length="middle" rot="R180"/>
<text x="-10.16" y="12.7" size="1.778" layer="94">Motor Controller Board</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="MICROCONTROLLER_BOARD">
<gates>
<gate name="G$1" symbol="MICROCONTROLLER_BOARD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICROCONTROLLER_BOARD">
<connects>
<connect gate="G$1" pin="+12V@1" pad="P$3"/>
<connect gate="G$1" pin="+12V@2" pad="P$4"/>
<connect gate="G$1" pin="+3V3@1" pad="P$1"/>
<connect gate="G$1" pin="+3V3@2" pad="P$2"/>
<connect gate="G$1" pin="BSY_X" pad="P$5"/>
<connect gate="G$1" pin="BSY_Y" pad="P$6"/>
<connect gate="G$1" pin="FLAG_X" pad="P$7"/>
<connect gate="G$1" pin="FLAG_Y" pad="P$8"/>
<connect gate="G$1" pin="GND@1" pad="P$9"/>
<connect gate="G$1" pin="GND@2" pad="P$10"/>
<connect gate="G$1" pin="LSR_EN" pad="P$11"/>
<connect gate="G$1" pin="SPI_CLK" pad="P$12"/>
<connect gate="G$1" pin="SPI_CS" pad="P$13"/>
<connect gate="G$1" pin="SPI_MISO" pad="P$14"/>
<connect gate="G$1" pin="SPI_MOSI" pad="P$15"/>
<connect gate="G$1" pin="STNBY_RST" pad="P$16"/>
<connect gate="G$1" pin="TILT" pad="P$17"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LASER_CONTROLLER_BOARD">
<gates>
<gate name="G$1" symbol="LASER_CONTROLLER_BOARD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LASER_CONTROLLER_BOARD">
<connects>
<connect gate="G$1" pin="+12V" pad="P$2"/>
<connect gate="G$1" pin="+3V3" pad="P$1"/>
<connect gate="G$1" pin="GND" pad="P$3"/>
<connect gate="G$1" pin="LSR_EN" pad="P$4"/>
<connect gate="G$1" pin="TILT" pad="P$5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MOTOR_CONTROLLER_BOARD">
<gates>
<gate name="G$1" symbol="MOTOR_CONTROLLER_BOARD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MOTOR_CONTROLLER_BOARD">
<connects>
<connect gate="G$1" pin="+12V" pad="P$2"/>
<connect gate="G$1" pin="+3V3" pad="P$1"/>
<connect gate="G$1" pin="BSY_X" pad="P$3"/>
<connect gate="G$1" pin="BSY_Y" pad="P$4"/>
<connect gate="G$1" pin="FLAG_X" pad="P$5"/>
<connect gate="G$1" pin="FLAG_Y" pad="P$6"/>
<connect gate="G$1" pin="GND" pad="P$7"/>
<connect gate="G$1" pin="SPI_CLK" pad="P$8"/>
<connect gate="G$1" pin="SPI_CS" pad="P$9"/>
<connect gate="G$1" pin="SPI_MISO" pad="P$10"/>
<connect gate="G$1" pin="SPI_MOSI" pad="P$11"/>
<connect gate="G$1" pin="STNBY_RST" pad="P$12"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="BlockDiagramBlocks" deviceset="MICROCONTROLLER_BOARD" device=""/>
<part name="U$2" library="BlockDiagramBlocks" deviceset="LASER_CONTROLLER_BOARD" device=""/>
<part name="U$3" library="BlockDiagramBlocks" deviceset="MOTOR_CONTROLLER_BOARD" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="22.86" y="22.86" size="6.4516" layer="91">Block Diagram</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="134.62" y="124.46"/>
<instance part="U$2" gate="G$1" x="132.08" y="195.58"/>
<instance part="U$3" gate="G$1" x="134.62" y="60.96"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="+3V3@1"/>
<wire x1="106.68" y1="139.7" x2="101.6" y2="139.7" width="0.1524" layer="91"/>
<wire x1="101.6" y1="139.7" x2="101.6" y2="170.18" width="0.1524" layer="91"/>
<wire x1="101.6" y1="170.18" x2="157.48" y2="170.18" width="0.1524" layer="91"/>
<wire x1="157.48" y1="170.18" x2="157.48" y2="205.74" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="+3V3"/>
<wire x1="157.48" y1="205.74" x2="154.94" y2="205.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="+12V"/>
<wire x1="154.94" y1="203.2" x2="160.02" y2="203.2" width="0.1524" layer="91"/>
<wire x1="160.02" y1="203.2" x2="160.02" y2="167.64" width="0.1524" layer="91"/>
<wire x1="160.02" y1="167.64" x2="99.06" y2="167.64" width="0.1524" layer="91"/>
<wire x1="99.06" y1="167.64" x2="99.06" y2="137.16" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="+12V@1"/>
<wire x1="99.06" y1="137.16" x2="106.68" y2="137.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="GND"/>
<wire x1="154.94" y1="200.66" x2="162.56" y2="200.66" width="0.1524" layer="91"/>
<wire x1="162.56" y1="200.66" x2="162.56" y2="165.1" width="0.1524" layer="91"/>
<wire x1="162.56" y1="165.1" x2="96.52" y2="165.1" width="0.1524" layer="91"/>
<wire x1="96.52" y1="165.1" x2="96.52" y2="134.62" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND@1"/>
<wire x1="96.52" y1="134.62" x2="106.68" y2="134.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="TILT"/>
<wire x1="154.94" y1="198.12" x2="165.1" y2="198.12" width="0.1524" layer="91"/>
<wire x1="165.1" y1="198.12" x2="165.1" y2="162.56" width="0.1524" layer="91"/>
<wire x1="165.1" y1="162.56" x2="93.98" y2="162.56" width="0.1524" layer="91"/>
<wire x1="93.98" y1="162.56" x2="93.98" y2="132.08" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="TILT"/>
<wire x1="93.98" y1="132.08" x2="106.68" y2="132.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="LSR_EN"/>
<wire x1="162.56" y1="139.7" x2="170.18" y2="139.7" width="0.1524" layer="91"/>
<wire x1="170.18" y1="139.7" x2="170.18" y2="220.98" width="0.1524" layer="91"/>
<wire x1="170.18" y1="220.98" x2="106.68" y2="220.98" width="0.1524" layer="91"/>
<wire x1="106.68" y1="220.98" x2="106.68" y2="205.74" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="LSR_EN"/>
<wire x1="106.68" y1="205.74" x2="109.22" y2="205.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="+3V3@2"/>
<wire x1="162.56" y1="137.16" x2="165.1" y2="137.16" width="0.1524" layer="91"/>
<wire x1="165.1" y1="137.16" x2="165.1" y2="96.52" width="0.1524" layer="91"/>
<wire x1="165.1" y1="96.52" x2="109.22" y2="96.52" width="0.1524" layer="91"/>
<wire x1="109.22" y1="96.52" x2="109.22" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="+3V3"/>
<wire x1="109.22" y1="68.58" x2="111.76" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="+12V@2"/>
<wire x1="162.56" y1="134.62" x2="167.64" y2="134.62" width="0.1524" layer="91"/>
<wire x1="167.64" y1="134.62" x2="167.64" y2="93.98" width="0.1524" layer="91"/>
<wire x1="167.64" y1="93.98" x2="106.68" y2="93.98" width="0.1524" layer="91"/>
<wire x1="106.68" y1="93.98" x2="106.68" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="+12V"/>
<wire x1="106.68" y1="66.04" x2="111.76" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND@2"/>
<wire x1="162.56" y1="132.08" x2="170.18" y2="132.08" width="0.1524" layer="91"/>
<wire x1="170.18" y1="132.08" x2="170.18" y2="91.44" width="0.1524" layer="91"/>
<wire x1="170.18" y1="91.44" x2="104.14" y2="91.44" width="0.1524" layer="91"/>
<wire x1="104.14" y1="91.44" x2="104.14" y2="63.5" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="GND"/>
<wire x1="104.14" y1="63.5" x2="111.76" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="SPI_CS"/>
<wire x1="162.56" y1="129.54" x2="172.72" y2="129.54" width="0.1524" layer="91"/>
<wire x1="172.72" y1="129.54" x2="172.72" y2="88.9" width="0.1524" layer="91"/>
<wire x1="172.72" y1="88.9" x2="101.6" y2="88.9" width="0.1524" layer="91"/>
<wire x1="101.6" y1="88.9" x2="101.6" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="SPI_CS"/>
<wire x1="101.6" y1="60.96" x2="111.76" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="SPI_MOSI"/>
<wire x1="162.56" y1="127" x2="175.26" y2="127" width="0.1524" layer="91"/>
<wire x1="175.26" y1="127" x2="175.26" y2="86.36" width="0.1524" layer="91"/>
<wire x1="175.26" y1="86.36" x2="99.06" y2="86.36" width="0.1524" layer="91"/>
<wire x1="99.06" y1="86.36" x2="99.06" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="SPI_MOSI"/>
<wire x1="99.06" y1="58.42" x2="111.76" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="SPI_CLK"/>
<wire x1="162.56" y1="124.46" x2="177.8" y2="124.46" width="0.1524" layer="91"/>
<wire x1="177.8" y1="124.46" x2="177.8" y2="83.82" width="0.1524" layer="91"/>
<wire x1="177.8" y1="83.82" x2="96.52" y2="83.82" width="0.1524" layer="91"/>
<wire x1="96.52" y1="83.82" x2="96.52" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="SPI_CLK"/>
<wire x1="96.52" y1="55.88" x2="111.76" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="STNBY_RST"/>
<wire x1="111.76" y1="53.34" x2="93.98" y2="53.34" width="0.1524" layer="91"/>
<wire x1="93.98" y1="53.34" x2="93.98" y2="81.28" width="0.1524" layer="91"/>
<wire x1="93.98" y1="81.28" x2="180.34" y2="81.28" width="0.1524" layer="91"/>
<wire x1="180.34" y1="81.28" x2="180.34" y2="121.92" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="STNBY_RST"/>
<wire x1="180.34" y1="121.92" x2="162.56" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="SPI_MISO"/>
<wire x1="157.48" y1="58.42" x2="160.02" y2="58.42" width="0.1524" layer="91"/>
<wire x1="160.02" y1="58.42" x2="160.02" y2="45.72" width="0.1524" layer="91"/>
<wire x1="160.02" y1="45.72" x2="88.9" y2="45.72" width="0.1524" layer="91"/>
<wire x1="88.9" y1="45.72" x2="88.9" y2="119.38" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="SPI_MISO"/>
<wire x1="88.9" y1="119.38" x2="106.68" y2="119.38" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="FLAG_Y"/>
<wire x1="157.48" y1="60.96" x2="162.56" y2="60.96" width="0.1524" layer="91"/>
<wire x1="162.56" y1="60.96" x2="162.56" y2="43.18" width="0.1524" layer="91"/>
<wire x1="162.56" y1="43.18" x2="86.36" y2="43.18" width="0.1524" layer="91"/>
<wire x1="86.36" y1="43.18" x2="86.36" y2="121.92" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="FLAG_Y"/>
<wire x1="86.36" y1="121.92" x2="106.68" y2="121.92" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="FLAG_X"/>
<wire x1="106.68" y1="124.46" x2="83.82" y2="124.46" width="0.1524" layer="91"/>
<wire x1="83.82" y1="124.46" x2="83.82" y2="40.64" width="0.1524" layer="91"/>
<wire x1="83.82" y1="40.64" x2="165.1" y2="40.64" width="0.1524" layer="91"/>
<wire x1="165.1" y1="40.64" x2="165.1" y2="63.5" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="FLAG_X"/>
<wire x1="165.1" y1="63.5" x2="157.48" y2="63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="BSY_Y"/>
<wire x1="106.68" y1="127" x2="81.28" y2="127" width="0.1524" layer="91"/>
<wire x1="81.28" y1="127" x2="81.28" y2="38.1" width="0.1524" layer="91"/>
<wire x1="81.28" y1="38.1" x2="167.64" y2="38.1" width="0.1524" layer="91"/>
<wire x1="167.64" y1="38.1" x2="167.64" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="BSY_Y"/>
<wire x1="167.64" y1="66.04" x2="157.48" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="BSY_X"/>
<wire x1="106.68" y1="129.54" x2="78.74" y2="129.54" width="0.1524" layer="91"/>
<wire x1="78.74" y1="129.54" x2="78.74" y2="35.56" width="0.1524" layer="91"/>
<wire x1="78.74" y1="35.56" x2="170.18" y2="35.56" width="0.1524" layer="91"/>
<wire x1="170.18" y1="35.56" x2="170.18" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="BSY_X"/>
<wire x1="170.18" y1="68.58" x2="157.48" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
