# SA-RSR-in-Ceph
SA-RSR: A Low-overhead Data Recovery Strategy for XOR-Coded Distributed Storage Systems
# abstract
To ensure the reliability and availability of data, redundancy strategies are always indispensable for distributed storage systems. As one of the generally-used redundancy strategies, erasure code has the advantage of low storage overhead which facilitates its employment in distributed storage systems. While among the various erasure codes, XOR-based erasure codes are becoming popular due to their fast computing speed. When some nodes fail in such a coded scheme, a process of data recovery takes place decoding for the lost data from the surviving ones, however, during which the data transmission consumes a considerable amount of time. To reduce the time consumed by data transmission, current researches mainly focus on reducing the data amount needed for data recovery but encounter problems such as high complexity and local optima. In this paper, we propose SA-RSR—a random search recovery algorithm for speeding up single-node failure recovery of XOR-based erasure codes—which uses a simulated annealing technique to search for a globally optimal recovery solution that uses a minimum amount of data and this search process can be done in polynomial time. We implement and evaluate SA-RSR in both simulations with a variety of XOR-based erasure codes and a real system Ceph. Experiments show that SA-RSR reduces the data amount required for recovery by 20%-30% and improves the performance of data recovery by 13%-20% in Ceph, compared with the conventional recovery method.
# SA-RSR
To integrate SA-RSR in the distributed storage system Ceph, we reconstruct the execution logic of the data recovery process of the Ceph erasure code. During data recovery, Ceph frst selects one OSD node to perform data recovery operations—usually the primary OSD node in the PG. We refer to this OSD as the recovery node.
According to the coding scheme in the PG and the number and location of the failed nodes, Ceph selects k surviving nodes to participate in the data recovery operation, including data nodes and parity nodes. In our design, when performing data recovery, we have the Recovery Scheduling login as: client-server
     ┌────────────────────────────────────────────────────────────────────┐
     │                        • MobaXterm 10.5 •                          │
     │            (SSH client, X-server and networking tools)             │
     │                                                                    │
     │ ➤ SSH session to client-server@202.117.10.101                      │
     │   • SSH compression : ✔                                            │
     │   • SSH-browser     : ✔                                            │
     │   • X11-forwarding  : ✔  (remote display is forwarded through SSH) │
     │   • DISPLAY         : ✔  (automatically set on remote server)      │
     │                                                                    │
     │ ➤ For more info, ctrl+click on help or visit our website           │
     └────────────────────────────────────────────────────────────────────┘

Last login: Mon Jan 21 15:08:54 2019 from 202.117.10.49
[client-server@client-server ~]$
[client-server@client-server ~]$ su
Password:
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd ceph/
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]#
[root@client-server ceph]# cd build/
[root@client-server build]#
[root@client-server build]# cd ..
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#

[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cp ./ceph/src/osd/
ClassHandler.cc       ECTransaction.cc      HitSet.h              OSD.h                 osd_types.h           PGTransaction.h       Session.cc
ClassHandler.h        ECTransaction.h       ObjectVersioner.h     osd_internal_types.h  PGBackend.cc          PrimaryLogPG.cc       Session.h
CMakeLists.txt        ECUtil.cc             OpRequest.cc          OSDMap.cc             PGBackend.h           PrimaryLogPG.h        SnapMapper.cc
ECBackend.cc          ECUtil.h              OpRequest.h           OSDMap.h              PG.cc                 ReplicatedBackend.cc  SnapMapper.h
ECBackend.h           ExtentCache.cc        OSDCap.cc             OSDMapMapping.cc      PG.h                  ReplicatedBackend.h   TierAgentState.h
ECMsgTypes.cc         ExtentCache.h         OSDCap.h              OSDMapMapping.h       PGLog.cc              ScrubStore.cc         Watch.cc
ECMsgTypes.h          HitSet.cc             OSD.cc                osd_types.cc          PGLog.h               ScrubStore.h          Watch.h
[root@client-server client-server]# cp ./ceph/src/osd/ECBackend.cc ./Ceph源码/OSD/EC
ECBackend.cc   ECBackend.h    ECMsgTypes.cc  ECMsgTypes.h   ECUtil.cc      ECUtil.h
[root@client-server client-server]# cp ./ceph/src/osd/ECBackend.cc ./Ceph源码/OSD/
cp: overwrite ‘./Ceph源码/OSD/ECBackend.cc’? y
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd Ceph源码/
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd OSD/
[root@client-server OSD]# ls
ECBackend.cc  ECBackend.h  ECMsgTypes.cc  ECMsgTypes.h  ECUtil.cc  ECUtil.h
[root@client-server OSD]# ll -h
total 164K
-rw-rw-r--. 1 client-server client-server 100K Jan 23 10:41 ECBackend.cc
-rw-rw-r--. 1 client-server client-server  26K Jan 20 21:15 ECBackend.h
-rw-rw-r--. 1 client-server client-server  12K Jan 20 21:15 ECMsgTypes.cc
-rw-rw-r--. 1 client-server client-server 4.2K Jan 20 21:15 ECMsgTypes.h
-rw-rw-r--. 1 client-server client-server 7.6K Jan 20 21:15 ECUtil.cc
-rw-rw-r--. 1 client-server client-server 5.6K Jan 20 21:15 ECUtil.h
[root@client-server OSD]#
[root@client-server OSD]#
[root@client-server OSD]#
[root@client-server OSD]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  OS  OSD
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# mv OS os
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  os  OSD
[root@client-server Ceph源码]# mv OSD osd
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# rm -rf ceph.conf
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR in ceph
mv: cannot stat ‘SA-RSR’: No such file or directory
mv: cannot stat ‘in’: No such file or directory
[root@client-server client-server]#
[root@client-server client-server]# mv -R Ceph源码/ SA-RSR in ceph
mv: invalid option -- 'R'
Try 'mv --help' for more information.
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR in ceph
mv: cannot stat ‘Ceph源码/’: No such file or directory
mv: cannot stat ‘SA-RSR’: No such file or directory
mv: cannot stat ‘in’: No such file or directory
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# find -name Ceph源码
./ceph/Ceph源码
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd ceph/
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]# mv Ceph源码/ ./
mv: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# cp Ceph源码/ ./
cp: omitting directory ‘Ceph源码/’
[root@client-server ceph]# cp -R  Ceph源码/ ./
cp: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]# cp -r  Ceph源码/ ./
cp: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]# cd Ceph源码/
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]# cd ..
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# mv -f Ceph源码/ ./
mv: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]# cd ...
bash: cd: ...: No such file or directory
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd ..
[root@client-server home]# cd client-server/
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]# cd ceph/
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# mv -f Ceph源码/ ../
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]#
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# ce Ceph源码/
bash: ce: command not found...
Similar command is: 'ci'
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd Ceph源码/
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd os
[root@client-server os]# ls
bluestore  filestore  kstore  memstore  ObjectStore.h
[root@client-server os]# cd filestore/
[root@client-server filestore]# ls
FileStore.cc  FileStore.h
[root@client-server filestore]# cd ..
[root@client-server os]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd  osd
[root@client-server osd]# ls
ECBackend.cc  ECBackend.h  ECMsgTypes.cc  ECMsgTypes.h  ECUtil.cc  ECUtil.h
[root@client-server osd]# vim ECBackend.cc
[root@client-server osd]#
[root@client-server osd]#
[root@client-server osd]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR_in_Ceph
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR_in_Ceph/
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# cd erasure-code/
[root@client-server erasure-code]#
[root@client-server erasure-code]# ls
CMakeLists.txt  ErasureCode.cc  ErasureCode.h  ErasureCodeInterface.h  ErasureCodePlugin.cc  ErasureCodePlugin.h  isa  jerasure  lrc  shec
[root@client-server erasure-code]# cd ..
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]# cd .
[root@client-server SA-RSR_in_Ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR_in_Ceph/
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# cd erasure-code/
[root@client-server erasure-code]# ls
CMakeLists.txt  ErasureCode.cc  ErasureCode.h  ErasureCodeInterface.h  ErasureCodePlugin.cc  ErasureCodePlugin.h  isa  jerasure  lrc  shec
[root@client-server erasure-code]# cd jerasure/
[root@client-server jerasure]# ls
CMakeLists.txt          ErasureCodeJerasure.h         ErasureCodePluginJerasure.h  jerasure          jerasure_init.h
ErasureCodeJerasure.cc  ErasureCodePluginJerasure.cc  gf-complete                  jerasure_init.cc
[root@client-server jerasure]# cd k
bash: cd: k: No such file or directory
[root@client-server jerasure]# cd jerasure/
[root@client-server jerasure]# ls
aclocal.m4  ChangeLog     configure     Examples  install-sh   m4           makefile.orig  NEWS      README.nd
AUTHORS     config.guess  configure.ac  include   License.txt  Makefile.am  Manual.pdf     PERF.txt  README.txt
autogen.sh  config.sub    COPYING       INSTALL   ltmain.sh    Makefile.in  missing        README    src
[root@client-server jerasure]# cd include/
[root@client-server include]#
[root@client-server include]# ls
cauchy.h  config.h.in  config.h.in~  control.h  galois.h  jerasure.h  liberation.h  reed_sol.h
[root@client-server include]# cd /home/client-server/
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#


[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#

[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# git clone https://github.com/lyfdamon/SA-RSR-in-Ceph.git
Cloning into 'SA-RSR-in-Ceph'...
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), done.
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  Templates  Videos
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    SA-RSR-in-Ceph  test.c
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR-in-Ceph/
[root@client-server SA-RSR-in-Ceph]# ls
README.md
[root@client-server SA-RSR-in-Ceph]#
[root@client-server SA-RSR-in-Ceph]# vim README.md
# SA-RSR-in-Ceph
SA-RSR: A Low-overhead Data Recovery Strategy for XOR-Coded Distributed Storage Systems
# abstract
To ensure the reliability and availability of data, redundancy strategies are always indispensable for distributed storage systems. As one of the generally-used redundancy strategies, erasure code has the advantage of low storage overhead which facilitates its employment in distributed storage systems. While among the various erasure codes, XOR-based erasure codes are becoming popular due to their fast computing speed. When some nodes fail in such a coded scheme, a process of data recovery takes place decoding for the lost data from the surviving ones, however, during which the data transmission consumes a considerable amount of time. To reduce the time consumed by data transmission, current researches mainly focus on reducing the data amount needed for data recovery but encounter problems such as high complexity and local optima. In this paper, we propose SA-RSR—a random search recovery algorithm for speeding up single-node failure recovery of XOR-based erasure codes—which uses a simulated annealing technique to search for a globally optimal recovery solution that uses a minimum amount of data and this search process can be done in polynomial time. We implement and evaluate SA-RSR in both simulations with a variety of XOR-based erasure codes and a real system Ceph. Experiments show that SA-RSR reduces the data amount required for recovery by 20%-30% and improves the performance of data recovery by 13%-20% in Ceph, compared with the conventional recovery method.
# SA-RSR
To integrate SA-RSR in the distributed storage system Ceph, we reconstruct the execution logic of the data recovery process of the Ceph erasure code. During data recovery, Ceph frst selects one OSD node to perform data recovery operations—usually the primary OSD node in the PG. We refer to this OSD as the recovery node.
According to the coding scheme in the PG and the number and location of the failed nodes, Ceph selects k surviving nodes to participate in the data recovery operation, including data nodes and parity nodes. In our design, when performing data recovery, we have the Recovery Scheduling login as: client-server
     ┌────────────────────────────────────────────────────────────────────┐
     │                        • MobaXterm 10.5 •                          │
     │            (SSH client, X-server and networking tools)             │
     │                                                                    │
     │ ➤ SSH session to client-server@202.117.10.101                      │
     │   • SSH compression : ✔                                            │
     │   • SSH-browser     : ✔                                            │
     │   • X11-forwarding  : ✔  (remote display is forwarded through SSH) │
     │   • DISPLAY         : ✔  (automatically set on remote server)      │
     │                                                                    │
     │ ➤ For more info, ctrl+click on help or visit our website           │
     └────────────────────────────────────────────────────────────────────┘

Last login: Mon Jan 21 15:08:54 2019 from 202.117.10.49
[client-server@client-server ~]$
[client-server@client-server ~]$ su
Password:
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd ceph/
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]#
[root@client-server ceph]# cd build/
[root@client-server build]#
[root@client-server build]# cd ..
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#

[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cp ./ceph/src/osd/
ClassHandler.cc       ECTransaction.cc      HitSet.h              OSD.h                 osd_types.h           PGTransaction.h       Session.cc
ClassHandler.h        ECTransaction.h       ObjectVersioner.h     osd_internal_types.h  PGBackend.cc          PrimaryLogPG.cc       Session.h
CMakeLists.txt        ECUtil.cc             OpRequest.cc          OSDMap.cc             PGBackend.h           PrimaryLogPG.h        SnapMapper.cc
ECBackend.cc          ECUtil.h              OpRequest.h           OSDMap.h              PG.cc                 ReplicatedBackend.cc  SnapMapper.h
ECBackend.h           ExtentCache.cc        OSDCap.cc             OSDMapMapping.cc      PG.h                  ReplicatedBackend.h   TierAgentState.h
ECMsgTypes.cc         ExtentCache.h         OSDCap.h              OSDMapMapping.h       PGLog.cc              ScrubStore.cc         Watch.cc
ECMsgTypes.h          HitSet.cc             OSD.cc                osd_types.cc          PGLog.h               ScrubStore.h          Watch.h
[root@client-server client-server]# cp ./ceph/src/osd/ECBackend.cc ./Ceph源码/OSD/EC
ECBackend.cc   ECBackend.h    ECMsgTypes.cc  ECMsgTypes.h   ECUtil.cc      ECUtil.h
[root@client-server client-server]# cp ./ceph/src/osd/ECBackend.cc ./Ceph源码/OSD/
cp: overwrite ‘./Ceph源码/OSD/ECBackend.cc’? y
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd Ceph源码/
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd OSD/
[root@client-server OSD]# ls
ECBackend.cc  ECBackend.h  ECMsgTypes.cc  ECMsgTypes.h  ECUtil.cc  ECUtil.h
[root@client-server OSD]# ll -h
total 164K
-rw-rw-r--. 1 client-server client-server 100K Jan 23 10:41 ECBackend.cc
-rw-rw-r--. 1 client-server client-server  26K Jan 20 21:15 ECBackend.h
-rw-rw-r--. 1 client-server client-server  12K Jan 20 21:15 ECMsgTypes.cc
-rw-rw-r--. 1 client-server client-server 4.2K Jan 20 21:15 ECMsgTypes.h
-rw-rw-r--. 1 client-server client-server 7.6K Jan 20 21:15 ECUtil.cc
-rw-rw-r--. 1 client-server client-server 5.6K Jan 20 21:15 ECUtil.h
[root@client-server OSD]#
[root@client-server OSD]#
[root@client-server OSD]#
[root@client-server OSD]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  OS  OSD
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# mv OS os
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  os  OSD
[root@client-server Ceph源码]# mv OSD osd
[root@client-server Ceph源码]# ls
ceph.conf  erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# rm -rf ceph.conf
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR in ceph
mv: cannot stat ‘SA-RSR’: No such file or directory
mv: cannot stat ‘in’: No such file or directory
[root@client-server client-server]#
[root@client-server client-server]# mv -R Ceph源码/ SA-RSR in ceph
mv: invalid option -- 'R'
Try 'mv --help' for more information.
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR in ceph
mv: cannot stat ‘Ceph源码/’: No such file or directory
mv: cannot stat ‘SA-RSR’: No such file or directory
mv: cannot stat ‘in’: No such file or directory
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# find -name Ceph源码
./ceph/Ceph源码
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd ceph/
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]# mv Ceph源码/ ./
mv: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# cp Ceph源码/ ./
cp: omitting directory ‘Ceph源码/’
[root@client-server ceph]# cp -R  Ceph源码/ ./
cp: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]# cp -r  Ceph源码/ ./
cp: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]# cd Ceph源码/
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]# cd ..
[root@client-server ceph]#
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# mv -f Ceph源码/ ./
mv: ‘Ceph源码/’ and ‘./Ceph源码’ are the same file
[root@client-server ceph]#
[root@client-server ceph]# cd ...
bash: cd: ...: No such file or directory
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# cd ..
[root@client-server home]# cd client-server/
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]# cd ceph/
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING           do_freebsd.sh    keys          PendingReleaseNotes  README.solaris         systemd
AUTHORS                   Ceph源码          COPYING-GPL2      Doxyfile         make-debs.sh  pom.xml              README.xio             udev
bin                       ChangeLog         COPYING-LGPL2.1   etc              make-dist     qa                   run-make-check.sh
build                     cmake             debian            examples         make-srpm.sh  README               selinux
ceph-erasure-code-corpus  CMakeLists.txt    doc               fusetrace        man           README.aix           share
ceph-object-corpus        CodingStyle       doc_deps.deb.txt  INSTALL          mirroring     README.FreeBSD       src
ceph.spec                 CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS          README.md            SubmittingPatches.rst
[root@client-server ceph]#
[root@client-server ceph]#
[root@client-server ceph]# mv -f Ceph源码/ ../
[root@client-server ceph]# ls
admin                     ceph.spec.in      COPYING-GPL2      Doxyfile         make-debs.sh         pom.xml         README.xio             udev
AUTHORS                   ChangeLog         COPYING-LGPL2.1   etc              make-dist            qa              run-make-check.sh
bin                       cmake             debian            examples         make-srpm.sh         README          selinux
build                     CMakeLists.txt    doc               fusetrace        man                  README.aix      share
ceph-erasure-code-corpus  CodingStyle       doc_deps.deb.txt  INSTALL          mirroring            README.FreeBSD  src
ceph-object-corpus        CONTRIBUTING.rst  do_cmake.sh       install-deps.sh  NEWS                 README.md       SubmittingPatches.rst
ceph.spec                 COPYING           do_freebsd.sh     keys             PendingReleaseNotes  README.solaris  systemd
[root@client-server ceph]#
[root@client-server ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]# ce Ceph源码/
bash: ce: command not found...
Similar command is: 'ci'
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd Ceph源码/
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd os
[root@client-server os]# ls
bluestore  filestore  kstore  memstore  ObjectStore.h
[root@client-server os]# cd filestore/
[root@client-server filestore]# ls
FileStore.cc  FileStore.h
[root@client-server filestore]# cd ..
[root@client-server os]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd  osd
[root@client-server osd]# ls
ECBackend.cc  ECBackend.h  ECMsgTypes.cc  ECMsgTypes.h  ECUtil.cc  ECUtil.h
[root@client-server osd]# vim ECBackend.cc
[root@client-server osd]#
[root@client-server osd]#
[root@client-server osd]# cd ..
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# ls
erasure-code  os  osd
[root@client-server Ceph源码]#
[root@client-server Ceph源码]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph  ceph_12.0.2.orig.tar.gz  Ceph源码  Desktop  Documents  Downloads  fr-ceph  hiredis  Music  Pictures  Public  redis  RRR  Templates  test.c  Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# mv Ceph源码/ SA-RSR_in_Ceph
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR_in_Ceph/
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# cd erasure-code/
[root@client-server erasure-code]#
[root@client-server erasure-code]# ls
CMakeLists.txt  ErasureCode.cc  ErasureCode.h  ErasureCodeInterface.h  ErasureCodePlugin.cc  ErasureCodePlugin.h  isa  jerasure  lrc  shec
[root@client-server erasure-code]# cd ..
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]# cd .
[root@client-server SA-RSR_in_Ceph]# cd ..
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR_in_Ceph/
[root@client-server SA-RSR_in_Ceph]# ls
erasure-code  os  osd
[root@client-server SA-RSR_in_Ceph]#
[root@client-server SA-RSR_in_Ceph]# cd erasure-code/
[root@client-server erasure-code]# ls
CMakeLists.txt  ErasureCode.cc  ErasureCode.h  ErasureCodeInterface.h  ErasureCodePlugin.cc  ErasureCodePlugin.h  isa  jerasure  lrc  shec
[root@client-server erasure-code]# cd jerasure/
[root@client-server jerasure]# ls
CMakeLists.txt          ErasureCodeJerasure.h         ErasureCodePluginJerasure.h  jerasure          jerasure_init.h
ErasureCodeJerasure.cc  ErasureCodePluginJerasure.cc  gf-complete                  jerasure_init.cc
[root@client-server jerasure]# cd k
bash: cd: k: No such file or directory
[root@client-server jerasure]# cd jerasure/
[root@client-server jerasure]# ls
aclocal.m4  ChangeLog     configure     Examples  install-sh   m4           makefile.orig  NEWS      README.nd
AUTHORS     config.guess  configure.ac  include   License.txt  Makefile.am  Manual.pdf     PERF.txt  README.txt
autogen.sh  config.sub    COPYING       INSTALL   ltmain.sh    Makefile.in  missing        README    src
[root@client-server jerasure]# cd include/
[root@client-server include]#
[root@client-server include]# ls
cauchy.h  config.h.in  config.h.in~  control.h  galois.h  jerasure.h  liberation.h  reed_sol.h
[root@client-server include]# cd /home/client-server/
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#


[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#

[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  test.c
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    Templates       Videos
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# git clone https://github.com/lyfdamon/SA-RSR-in-Ceph.git
Cloning into 'SA-RSR-in-Ceph'...
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), done.
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# ls
ceph                     Desktop    Downloads  hiredis  Pictures  redis  SA-RSR_in_Ceph  Templates  Videos
ceph_12.0.2.orig.tar.gz  Documents  fr-ceph    Music    Public    RRR    SA-RSR-in-Ceph  test.c
[root@client-server client-server]#
[root@client-server client-server]#
[root@client-server client-server]# cd SA-RSR-in-Ceph/
[root@client-server SA-RSR-in-Ceph]# ls
README.md
[root@client-server SA-RSR-in-Ceph]#
[root@client-server SA-RSR-in-Ceph]# vim README.md
# SA-RSR-in-Ceph
SA-RSR: A Low-overhead Data Recovery Strategy for XOR-Coded Distributed Storage Systems
# abstract
To ensure the reliability and availability of data, redundancy strategies are always indispensable for distributed storage systems. As one of the generally-used redundancy strategies, erasure code has the advantage of low storage overhead which facilitates its employment in distributed storage systems. While among the various erasure codes, XOR-based erasure codes are becoming popular due to their fast computing speed. When some nodes fail in such a coded scheme, a process of data recovery takes place decoding for the lost data from the surviving ones, however, during which the data transmission consumes a considerable amount of time. To reduce the time consumed by data transmission, current researches mainly focus on reducing the data amount needed for data recovery but encounter problems such as high complexity and local optima. In this paper, we propose SA-RSR—a random search recovery algorithm for speeding up single-node failure recovery of XOR-based erasure codes—which uses a simulated annealing technique to search for a globally optimal recovery solution that uses a minimum amount of data and this search process can be done in polynomial time. We implement and evaluate SA-RSR in both simulations with a variety of XOR-based erasure codes and a real system Ceph. Experiments show that SA-RSR reduces the data amount required for recovery by 20%-30% and improves the performance of data recovery by 13%-20% in Ceph, compared with the conventional recovery method.
# SA-RSR
To integrate SA-RSR in the distributed storage system Ceph, we reconstruct the execution logic of the data recovery process of the Ceph erasure code. During data recovery, Ceph frst selects one OSD node to perform data recovery operations—usually the primary OSD node in the PG. We refer to this OSD as the recovery node.
According to the coding scheme in the PG and the number and location of the failed nodes, Ceph selects k surviving nodes to participate in the data recovery operation, including data nodes and parity nodes. In our design, when performing data recovery, we have the Recovery Scheduling Module with which Ceph executes SA-RSR on the recovery node to obtain a symbol reading scheme with the smallest amount of data, which corresponds to the surviving nodes in the PG. According to the symbol reading scheme, the recovery node constructs a reading request for each node involved in the data recovery process. Once the reading requests are built, they are sent to corresponding nodes.
A Recovery Read Handler runs on each surviving node and handles the read requests sent by the recovery node. The OSD Daemons in Ceph are responsible for reading data blocks from the disk. Based on this system design, the Recovery Read Handler performs data read operations according to the messages in the read requests, which contain the ids of the symbols that the current node needs to read. All symbols needed for data recovery are sent back to the recovery node.
The missing data can be obtained by the decoding operation of the Decoding Module. Ceph uses an erasure code plug-in infrastructure that enables dynamical use of external erasure code libraries, while the XOR-based erasure codes are implemented in the Jerasure-2.0 Library in Ceph. Therefore, we improve the decoding part of the Jerasure Library to ensure that it can decode the lost data with less data.
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
-- INSERT --                                                                                                                               7,286         All

~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
~
-- INSERT --                                                                                                                               7,286         All

