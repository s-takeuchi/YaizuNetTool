=================================================
StkFw 1.5.0
=================================================
1.Summary of StkFw

StkFw is a test support software solution that simulates environments in
which multiple pieces of software and/or hardware work together on an
IP network.
In the development of software designed to work and cooperate with complex
and valuable elements (software and/or hardware) on a network, the use of
a testing program that simulates network element behavior is a well-known
solution for reducing overall development costs.
However, if the behavior (i.e., communication with other network elements)
of the software being developed is complex, the initial costs of creating
a test program may be high.

StkFw can be used to facilitate the control of data communication on an
IP network based on its superior user interface. It simulates behavior
identical to that of testing programs and reduces the overall cost of
testing during the target software's development by eliminating the need
to create a dedicated testing program.


=================================================
2.System requirements

StkFw works on systems with the following specifications:

CPU: 1 GHz or more

Memory: 512 MB or more

Free disk space: 20 MB or more

Operating systems/editions supported:
Windows 2000 Professional SP4
Windows XP Professional SP3
Windows XP Professional x64 SP2
Windows Vista Business/Ultimate SP2
Windows 7 Professional/Ultimate SP1
Windows 8 Pro
Windows Server 2003 Standard SP2
Windows Server 2003 R2 Standard SP2
Windows Server 2008 Standard SP2
Windows Server 2008 R2 Standard SP1
Windows Server 2012 Standard


=================================================
3.Change history
* Version 1.0.0 ---> 1.1.0
(1) The bug involving the folder for loaded/saved repository data being
    configured as the initial folder after restarting StkFw was fixed.
(2) The bug involving the icon name being misaligned from the center of the
    icon was fixed.
(3) The purpose of the software was changed from provision of a test
    framework to testing support.
(4) Support for addition/removal of a loopback network adapter dialog was
    added.
(5) A bug in the Add/remove IP address wizard involving the flushing of
    added/removed IP addresses after operating system reboot was fixed.
(6) Support for variable management functionality (Variable Controller)
    was added.

* Version 1.1.0 ---> 1.2.0
(1) Support enabled for StkFw operation by non-administrator-group users.
(2) Support enabled for communication logging functionality on thread
    controller.
(3) Support enabled for Windows 7, Windows Server 2003 and Windows Server
    2008.
(4) Support enabled for simultaneous launch of multiple main consoles.
(5) Support enabled for thread execution as a background process.
(6) Support enabled for import and export of multiple variable
    specifications.
(7) Fixed bug whereby data flow in which multiple threads leading to a single
    thread did not terminate even when processing reached the end of the
    element.
(8) Bugs relating to invalid data overwritten and unnecessary data processing
    on data flow in which multiple threads led to a single thread have been
    fixed.

* Version 1.2.0 ---> 1.3.0
(1) Support enabled for writing/reading of file processing elements.
(2) Support enabled for processing of elements that execute external
    programs.
(3) Support enabled for start/stop all threads function.
(4) Support enabled for specification of TCP receiver termination conditions.
    Detection of excess data length and data matching newly added as
    termination conditions.

* Version 1.3.0 ---> 1.4.0
(1) Support enabled for two socket closure methods (forced close and peer
    shutdown detection close).
(2) Support enabled for workspace size change.
(3) Support enabled for hierarchical menu for addition of processing element
    operations.
(4) Support enabled for UDP receiver processing element and UDP sender
    processing element.
(5) Logged bug relating to invalid ID for processing element fixed.
(6) Support enabled for Windows 8, Windows Server 2012, Windows Server 2003 R2
    and Windows Server 2008 R2.

* Version 1.4.0 ---> 1.5.0
(1) Installer program files integrated into one MSI file.
(2) Support enabled for multiple client's connections using same port number.
(3) A bug fixed that the redundant logs of socket closing for same element are
    generated when threads are stopping.
(4) A bug fixed that the current folder is not configured as the folder where
    .std file placed when the program launched with /open and /start parameter.


=================================================
4.Installation

Execute stkfw.msi and launch the installer.
Follow the on-screen dialog prompts.


=================================================
5.Contact

Please use the E-mail address below for inquiries about this product.

bamboo@rj.dream.jp
Shinya Takeuchi

