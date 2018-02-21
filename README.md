# protoDEV-coreXY
coreXY direct drive extruder 3D printer running Smootieware firmware

---------------------------------------------------------------------

 About:
 
 What is working here?
 
 Hmmm... Everything? 
 
 This is not an another incomplete "work in progress" project.
 It's a work in progress project that has improvment in mind.
 
 I'm into 3dprinting for about 5 years, and active building 3d printers for at least 4 years.
 Learned a lot thanks to the community... and the LORD Prusa ;)
 Internet is a place were some got news, youtube, porn...
 and some having nerd stuff... software, mechanical, electrical and electronical articles, blogs, vlogs, faqs etc.
 If you are a tech Nerd just like me, you can find tons of very interesting educational articles that can build up your knowlage until...
 everything ended up on GitHub.
 Why?
 because was living the 3dprinter hype and tested all the bullshit and non-bulshit projects on te planet.
 
 Now it's time to share some of the knowlage just like all those people all over the world shared with me.
 
 My goal is to gather some people that will/want to build, use and improve the project.
 I've spent about 3 months working on the Cad3D part (SolidWorks) of the project to make parts simple to print and simple to build.
 Most of those 3 months was a the path of math and symetry... and off course... aggressive wife :P
 Then had to spent some time working on Smoothieware firmware to suit the system.
 After that been studying how printer moves in slo-mo to further improve the config and mechanics.
 
 I wanted to print with parameters equal to Prusa i3 Mk3 and now got even beyond... 
 
 The next big thing comming... 24V power supply upgrade. 
 I've calculated thet in theory the system should run print speeds beyond 375mm/s
 To make the mechanics hold up the new speed need to loose some x-axis weight.
 The idea is to lose >100g by changing 2x 8mm steel rods with 1x hiwin rail
 or >200g by changing steel rods and LM8UU to carbon fiber pipes and polymer Igus linear bearings.
 Hiwin is hevier then carbon pipes but the hiwin cartige has lot stiffer moves than LM8UU/IGUS bearings.
 
 Features:
 
 - 32bit Smoothieware firmware for smooth motion
 - no-crossing belts symetrical coreXY for hi-torque and stiffness
 - geared direct drive extuder (simpler and more reliable printing then bowden)
 - hi-flow quality hotend (e3d hotend with volcano heat block) for high quality fast printing
 - all axis with 2x higher mechanical resolution at same steprate (0.9deg motors with 8x microstepping)
 - one motor doubble z-axis (no problems to sync motors because got just one for both bed side lifters)
 - all axis motors mounted at bottom of printer to lower the center of gravity 
    (if your printer likes jumping all over the room when printing, 
	lowering the center of gravity near ground can compensate the "heavy mass" 
	running in XY directions at top of printer pulling the lighter lower part of system )
 - 12V system printing up to 220mm/s and accleration at 3500mm/s2 (on 24V theoretical >375mm/s)
 - all of non-printed parts was selected to be worldwide availabe and have resonable price to quality ratio.
 
 TODO:
 
 -Cleanup filenames in solidworks project
 -Cleanup stl folder (right now it's pure project .stl dump, so lots of files not need to be printed)
 -fist of parts
 -build instruction
 -firmware/software manual
 -BOM for all non-printed parts 
 -Test 24V system theoretical print speed >375mm/s 
 -Build a test Hiwin x-axis 
 -Build a test carbon fiber rods + igus bearings x-axis
 -???

 
