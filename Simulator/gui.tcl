#!/usr/bin/wish

# Modify the above line to reflect the correct path for wish in your system
#
# Graphical User Interface for simulating datalink protocols.
# 
# Written by Shivakant Mishra


# Set window title

wm title . {Simulator for Datalink Protocols}

# Create a frame for help and quit buttons.

frame .qframe -borderwidth 10
pack .qframe -side top -fill x

# Create the quit button.

button .qframe.help -text Help -command help_window
button .qframe.quit -text Quit -command exit
pack .qframe.quit -side right
pack .qframe.help -side right
pack .qframe -side top -fill both -expand true

# Create frame for compilation

frame .compile -borderwidth 10
label .compile.l -text {COMPILE SIMULATOR AND PROTOCOLS:} -padx 0

menubutton .compile.makemenu -text Make -menu .compile.makemenu.menu
set m [menu .compile.makemenu.menu]
$m add command -label make -command make_proc
$m add command -label {make protocol2} -command {make_proc protocol2}
$m add command -label {make protocol3} -command {make_proc protocol3}
$m add command -label {make protocol4} -command {make_proc protocol4}
$m add command -label {make protocol5} -command {make_proc protocol5}
$m add command -label {make protocol6} -command {make_proc protocol6}
$m add command -label {make clean} -command {make_proc clean}

pack .compile.l -side left
pack .compile.makemenu -side left
pack .compile -side top -fill both -expand true

# Create frames for collecing protocol parameters

frame .middle -borderwidth 10
label .middle.l -text {PROTOCOL PARAMETERS:} 
pack .middle.l -side left
pack .middle -side top -fill both -expand true

frame .middle2 -borderwidth 2
label .middle2.filler1 -text {} -padx 20
label .middle2.e -text Events: -padx 0
entry .middle2.ev -width 10 -relief sunken -textvariable events
set events 100
label .middle2.t -text Ticks: -padx 0
entry .middle2.tc -width 10 -relief sunken -textvariable ticks
set ticks 40
label .middle2.pkl -text {Packet Loss:} -padx 0
entry .middle2.pkll -width 10 -relief sunken -textvariable pkt_loss
set pkt_loss 0

pack .middle2.filler1 -side left
pack .middle2.e -side left
pack .middle2.ev -side left
pack .middle2.t -side left
pack .middle2.tc -side left 
pack .middle2.pkl -side left
pack .middle2.pkll -side left 
pack .middle2 -side top -fill both -expand true

frame .middle3 -borderwidth 2
label .middle3.filler1 -text {} -padx 20
label .middle3.ck -text {Garbled Rate:} -padx 0
entry .middle3.ckk -width 10 -relief sunken -textvariable cksum
set cksum 0
label .middle3.d -text Debug?: -padx 0
entry .middle3.db -width 10 -relief sunken -textvariable debug
set debug 0

pack .middle3.filler1 -side left
pack .middle3.ck -side left
pack .middle3.ckk -side left
pack .middle3.d -side left
pack .middle3.db -side left
pack .middle3 -side top -fill both -expand true

# Create frames for running various protocols

frame .running -borderwidth 10
label .running.l -text {PROTOCOL EXECUTION:}
pack .running.l -side left
pack .running -side top -fill both -expand true

frame .running2 -borderwidth 5
label .running2.filler1 -text {} -padx 20
label .running2.f -text {Output Filename:} -padx 0
entry .running2.ofn -width 40 -relief sunken -textvariable fname

menubutton .running2.protocolmenu -text {Run Protocol} \
	-menu .running2.protocolmenu.menu
set pm [menu .running2.protocolmenu.menu -tearoff 1]
$pm add command -label {Protocol 2} -command {run_protocol protocol2}
$pm add command -label {Protocol 3} -command {run_protocol protocol3}
$pm add command -label {Protocol 4} -command {run_protocol protocol4}
$pm add command -label {Protocol 5} -command {run_protocol protocol5}
$pm add command -label {Protocol 6} -command {run_protocol protocol6}

pack .running2.filler1 -side left
pack .running2.f -side left
pack .running2.ofn -side left
pack .running2.protocolmenu -side right
pack .running2 -side top -fill both -expand true


# Create a text widget to log the output

frame .t
set log [text .t.log -width 80 -height 10 \
	-borderwidth 2 -relief raised -setgrid true \
	-yscrollcommand {.t.scroll set}]
scrollbar .t.scroll -command {.t.log yview}
pack .t.scroll -side right -fill y
pack .t.log -side left -fill both -expand true
pack .t -side top -fill both -expand true

# Run make

proc make_proc {{w all}} {
  global input log

  if [catch {open "|make $w |& cat"} input] {
    $log insert end $input\n
  } else {
    fileevent $input readable Log
    $log insert end make\n
  }
}

# Run Protocols

proc run_protocol {{w protocol2}} {
  global input log events ticks pkt_loss cksum debug fname fileid flag

  set flag 0
  if {[string compare $fname {}] != 0} {
    set flag 1
    if [catch {open $fname {WRONLY CREAT}} fileid] {
      $log insert end $fileid\n
      return
    }
  } 
  if [catch {open "|./$w $events $ticks $pkt_loss $cksum \
	$debug |& cat"} input] {
    $log insert end $input\n
    if {$flag == 1} {
      catch {close $fileid}
    }
  } else {
    if {$flag == 1} {
      fileevent $input readable Log_file
    } else {
      fileevent $input readable Log
    }
    $log insert end $w\n
  }
}

# Read and log output from the program

proc Log {} {
  global input log

  if [eof $input] {
    Stop
    $log insert end DONE\n
    $log see end
  } else {
    gets $input line
    $log insert end $line\n
    $log see end
  }
}

proc Log_file {} {
  global input log fileid

  if [eof $input] {
    Stop_file
    $log insert end DONE\n
    $log see end
  } else {
    gets $input line
    puts $fileid $line
  }
}


# Stop the program and close the files

proc Stop {} {
  global input but

  catch {close $input}
}

proc Stop_file {} {
  global input but fileid

  catch {close $input}
  catch {close $fileid} 
}

proc help_window {} {
  global f

  set f [toplevel .helpframe -borderwidth 10]
  grab $f
  message $f.msg -text {To compile the simulator and protocols:
    Click on make menu and choose appropriate option.


To run protocols:
    1. Enter the values of five simulator parameters
    2. Enter a filename if you want to store output in a file
    3. Click on Run Protocol menu and choose appropriate protocol to run.


To exit:
    Click on the Quit button.}
  set b [frame $f.buttons -bd 10]
  pack $f.msg $f.buttons -side top -fill x
  button $b.ok -text OK -underline 0 -command {global f; grab release $f; destroy $f}
  pack $b.ok -side top 
}
