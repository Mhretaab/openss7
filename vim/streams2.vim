syn keyword Special CD_ATTACH_PENDING CD_DETACH_PENDING
syn keyword Special I_ANCHOR I_ATMARK I_SETCLTIME I_GETCLTIME I_CANPUT I_SERROPT
syn keyword Special I_GERROPT I_PUTPMSG I_GETPMSG I_FATTACH I_FDETACH I_PIPE
syn keyword Special I_GRDOPT I_STR I_SETSIG I_GETSIG I_FIND I_LINK I_UNLINK
syn keyword Special I_LIST I_PLINK I_PUNLINK I_FLUSHBAND I_CKBAND I_GETBAND
syn keyword Special I_PEEK I_FDINSERT I_SENDFD I_RECVFD I_SWROPT I_GWROPT
syn keyword Special M_DATA M_PROTO M_BREAK M_CTL M_DELAY M_IOCTL M_PASSFP M_RSE
syn keyword Special M_IOCACK M_IOCNAK M_IOCDATA M_PCPROTO M_PCRSE M_PCSIG M_READ
syn keyword Special M_SETOPTS M_SIG M_COPYIN M_COPYOUT M_ERROR M_FLUSH M_HANGUP
syn keyword Special M_STOP M_START M_STARTI M_STOPI M_UNHANGUP
syn keyword Special M_PCCTL M_PCSETOPTS M_LETSPLAY M_BACKWASH M_BACKDONE
syn keyword Special M_DONTPLAY M_EVENT M_PCEVENT
syn keyword Special __SID STR I_NREAD I_PUSH I_POP I_LOOK I_FLUSH I_SRDOPT
syn keyword Constant ANYBAND DRVOPEN MODOPEN CLONEOPEN
syn keyword Constant CD_BADFRAME CD_BADPPA CD_BADPRIM CD_DISC CD_EVENT CD_FATALERR CD_INITFAILED
syn keyword Constant CD_CANREAD CD_CANDIAL CD_AUTOALLOW CD_KEEPALIVE CD_STYLE1 CD_STYLE2 CD_STYLE_1
syn keyword Constant CD_CRCERR CD_DLE_EOT CD_FORMAT CD_HDLC_ABORT CD_OVERRUN CD_TOOSHORT
syn keyword Constant CD_DISABLE_REQ CD_OK_ACK CD_ERROR_ACK CD_ENABLE_CON CD_DISABLE_CON
syn keyword Constant CD_ENABLED CD_READ_ACTIVE CD_INPUT_ALLOWED CD_DISABLE_PENDING CD_OUTPUT_ACTIVE
syn keyword Constant CD_ERROR_IND CD_ALLOW_INPUT_REQ CD_READ_REQ CD_UNITDATA_REQ CD_WRITE_READ_REQ
syn keyword Constant CD_FRM_ABORTED CD_RCV_OVERRUN CD_DTR CD_RTS CD_DSR CD_DCD CD_CTS CD_RI
syn keyword Constant CD_FULLDUPLEX CD_HALFDUPLEX CD_UNACKEDOUTPUT CD_ACKEDOUTPUT CD_PACEDOUTPUT
syn keyword Constant CD_IMPLICIT CD_FRMTOOLONG CD_FRMNONOCTET CD_EMPTY_BFR CD_BAD_CRC
syn keyword Constant CD_INCOMPLETE CD_BUSY CD_NOANSWER CD_CALLREJECT CD_HDLC_IDLE CD_HDLC_NOTIDLE
syn keyword Constant CD_INFO_REQ CD_INFO_ACK CD_ATTACH_REQ CD_DETACH_REQ CD_ENABLE_REQ
syn keyword Constant CD_LAN_NOSTATION CD_LOSTCTS CD_DEVERR CD_HDLC CD_BISYNC CD_LAN CD_NODEV CD_DAED
syn keyword Constant CD_MODEM_SIG_POLL CD_UNATTACHED CD_UNUSABLE CD_DISABLED CD_ENABLE_PENDING
syn keyword Constant CD_MUX_NAME_REQ CD_BAD_FRAME_IND CD_MODEM_SIG_REQ CD_MODEM_SIG_IND
syn keyword Constant CD_NOTSUPP CD_OUTSTATE CD_PROTOSHORT CD_READTIMEOUT CD_SYSERR CD_WRITEFAIL
syn keyword Constant CD_QUIESCENT CD_RESUMED CD_DSRTIMEOUT CD_LAN_COLLISIONS CD_LAN_REFUSED
syn keyword Constant CD_STYLE_2 CD_NODIAL CD_FLUSH CD_WAIT CD_DELIVER CD_SPECIFIC CD_BROADCAST
syn keyword Constant CD_UNITDATA_ACK CD_UNITDATA_IND CD_HALT_INPUT_REQ CD_ABORT_OUTPUT_REQ
syn keyword Constant CD_XRAY CD_BADADDRESS CD_BADADDRTYPE CD_BADDIAL CD_BADDIALTYPE CD_BADDISPOSAL
syn keyword Constant CE_NOTE CE_WARN CE_PANIC
syn keyword Constant CHF_RX_DIR CHF_TX_DIR CHF_BOTH_DIR
syn keyword Constant CHOUTSTATE CHBADOPT CHBADPARM CHBADPARMTYPE CHBADFLAG CHBADPRIM CHNOTSUPP
syn keyword Constant CHS_UNUSABLE CHS_DETACHED CHS_WACK_AREQ CHS_WACK_UREQ CHS_ATTACHED
syn keyword Constant CHS_WACK_CREQ CHS_WCON_CREQ CHS_WACK_DREQ CHS_WCON_DREQ CHS_CONNECTED
syn keyword Constant CHS_WACK_EREQ CHS_WCON_EREQ CHS_WACK_RREQ CHS_WCON_RREQ CHS_ENABLED
syn keyword Constant CH_DATA_REQ CH_DISCONNECT_REQ CH_DISABLE_REQ CH_DETACH_REQ CH_INFO_ACK
syn keyword Constant CH_DISCONNECT_IND CH_DISCONNECT_CON CH_DISABLE_IND CH_DISABLE_CON CHS_UNINIT
syn keyword Constant CH_ENCODING_FS1015 CH_ENCODING_FS1016 CH_ENCODING_G711_PCM_A
syn keyword Constant CH_ENCODING_G711_PCM_L CH_ENCODING_G711_PCM_U CH_ENCODING_G721
syn keyword Constant CH_ENCODING_G722 CH_ENCODING_G723 CH_ENCODING_G726 CH_ENCODING_G728
syn keyword Constant CH_ENCODING_G729 CH_ENCODING_GSM CH_ENCODING_GSM_EFR CH_ENCODING_GSM_HR
syn keyword Constant CH_ENCODING_LPC CH_ENCODING_MPA CH_ENCODING_QCELP CH_ENCODING_RED
syn keyword Constant CH_ENCODING_S16_BE CH_ENCODING_S16_LE CH_ENCODING_S8 CH_ENCODING_U16_BE
syn keyword Constant CH_ENCODING_U16_LE CH_ENCODING_U8 CH_ENCODING_VDVI CH_RATE_VARIABLE
syn keyword Constant CH_INFO_REQ CH_OPTMGMT_REQ CH_ATTACH_REQ CH_ENABLE_REQ CH_CONNECT_REQ
syn keyword Constant CH_OPTMGMT_ACK CH_OK_ACK CH_ERROR_ACK CH_ENABLE_CON CH_CONNECT_CON CH_DATA_IND
syn keyword Constant CH_PARM_OPT_CLRCH CH_ENCODING_NONE CH_ENCODING_CN CH_ENCODING_DVI4
syn keyword Constant CH_RATE_8000 CH_RATE_11025 CH_RATE_16000 CH_RATE_22050 CH_RATE_44100
syn keyword Constant CH_RATE_90000 CH_SET CH_GET CH_NEGOTIATE CH_DEFAULT CHSYSERR CHBADADDR
syn keyword Constant CH_STYLE1 CH_STYLE2 CH_VERSION_1_0 CH_VERSION CH_PARMS_CIRCUIT
syn keyword Constant DL_ACCESS DL_BADADDR DL_BADCORR DL_BADDATA DL_BADPPA DL_BADPRIM DL_BADQOSPARAM
syn keyword Constant DL_ATTACH_PENDING DL_DETACH_PENDING DL_UNBOUND DL_BIND_PENDING
syn keyword Constant DL_BADQOSTYPE DL_BADSAP DL_BADTOKEN DL_BOUND DL_INITFAILED DL_NOADDR
syn keyword Constant DL_CMD_PE DL_CMD_IP DL_CMD_UN DL_CMD_IT DL_RSP_MASK DL_RSP_OK DL_RSP_RS
syn keyword Constant DL_CONNECT_IND DL_CONNECT_RES DL_CONNECT_CON DL_TOKEN_REQ DL_TOKEN_ACK
syn keyword Constant DL_CONN_RES_PENDING DL_DATAXFER DL_USER_RESET_PENDING DL_PROV_RESET_PENDING
syn keyword Constant DL_CONREJ_DEST_UNREACH_PERMANENT DL_CONREJ_DEST_UNREACH_TRANSIENT
syn keyword Constant DL_CONREJ_PERMANENT_COND DL_CONREJ_TRANSIENT_COND DL_DISC_ABNORMAL_CONDITION
syn keyword Constant DL_CONREJ_QOS_UNAVAIL_PERMANENT DL_CONREJ_QOS_UNAVAIL_TRANSIENT
syn keyword Constant DL_CURRENT_VERSION DL_VERSION_2 DL_INFO_REQ DL_INFO_ACK DL_ATTACH_REQ
syn keyword Constant DL_DETACH_REQ DL_BIND_REQ DL_BIND_ACK DL_UNBIND_REQ DL_SUBS_BIND_REQ
syn keyword Constant DL_DISCON12_PENDING DL_DISCON13_PENDING DL_SUBS_BIND_PND DL_SUBS_UNBIND_PND
syn keyword Constant DL_DISCONNECT_REQ DL_DISCONNECT_IND DL_RESET_REQ DL_RESET_IND DL_RESET_RES
syn keyword Constant DL_DISC_NORMAL_CONDITION DL_DISC_PERMANENT_CONDITION
syn keyword Constant DL_DISC_TRANSIENT_CONDITION DL_DISC_UNSPECIFIED DL_RESET_FLOW_CONTROL
syn keyword Constant DL_FACT_PHYS_ADDR DL_CURR_PHYS_ADDR DL_POLL_FINAL DL_AUTO_XID DL_AUTO_TEST
syn keyword Constant DL_FRAME DL_MPFRAME DL_ASYNC DL_IPX25 DL_LOOP DL_CODLS DL_CLDLS DL_ACLDLS
syn keyword Constant DL_IPATM DL_X25 DL_ISDN DL_HIPPI DL_100VG DL_100VGTPR DL_ETH_CSMA DL_100BT
syn keyword Constant DL_METRO DL_ETHER DL_HDLC DL_CHAR DL_CTCA DL_FDDI DL_OTHER DL_FC DL_ATM
syn keyword Constant DL_NOTESTAUTO DL_XIDAUTO DL_TESTAUTO DL_PENDING DL_CSMACD DL_TPB DL_TPR
syn keyword Constant DL_NOTINIT DL_OUTSTATE DL_SYSERR DL_UNSUPPORTED DL_UNDELIVERABLE
syn keyword Constant DL_NOTSUPPORTED DL_TOOMANY DL_NOTENAB DL_BUSY DL_NOAUTO DL_NOXIDAUTO
syn keyword Constant DL_PEER_BIND DL_HIERARCHICAL_BIND DL_PROMISC_PHYS DL_PROMISC_SAP
syn keyword Constant DL_PROMISCON_REQ DL_PROMISCOFF_REQ DL_OK_ACK DL_ERROR_ACK DL_CONNECT_REQ
syn keyword Constant DL_PROMISC_MULTI
syn keyword Constant DL_QOS_CO_RANGE1 DL_QOS_CO_SEL1 DL_QOS_CL_RANGE1 DL_QOS_CL_SEL1
syn keyword Constant DL_REPLY_REQ DL_REPLY_IND DL_REPLY_STATUS_IND DL_REPLY_UPDATE_REQ
syn keyword Constant DL_REPLY_UPDATE_STATUS_IND DL_PHYS_ADDR_REQ DL_PHYS_ADDR_ACK
syn keyword Constant DL_RESET_CON DL_UNITDATA_REQ DL_UNITDATA_IND DL_UDERROR_IND DL_UDQOS_REQ
syn keyword Constant DL_RESET_LINK_ERROR DL_RESET_RESYNCH DL_CMD_MASK DL_CMD_OK DL_CMD_RS DL_CMD_UE
syn keyword Constant DL_RESET_RES_PENDING DL_DISCON8_PENDING DL_DISCON9_PENDING DL_DISCON11_PENDING
syn keyword Constant DL_RQST_NORSP DL_NONE DL_MONITOR DL_MAXIMUM DL_UNKNOWN DL_QOS_DONT_CARE
syn keyword Constant DL_RSP_NE DL_RSP_NR DL_RSP_UE DL_RSP_IP DL_RSP_UN DL_RSP_IT DL_RQST_RSP
syn keyword Constant DL_SET_PHYS_ADDR_REQ DL_GET_STATISTICS_REQ DL_GET_STATISTICS_ACK DL_UNATTACHED
syn keyword Constant DL_STYLE1 DL_STYLE2 DL_PROVIDER DL_USER DL_CONREJ_DEST_UNKNOWN
syn keyword Constant DL_SUBS_BIND_ACK DL_SUBS_UNBIND_REQ DL_ENABMULTI_REQ DL_DISABMULTI_REQ
syn keyword Constant DL_TEST_REQ DL_TEST_IND DL_TEST_RES DL_TEST_CON DL_XID_REQ DL_XID_IND
syn keyword Constant DL_UNBIND_PENDING DL_IDLE DL_UDQOS_PENDING DL_OUTCON_PENDING DL_INCON_PENDING
syn keyword Constant DL_XID_RES DL_XID_CON DL_DATA_ACK_REQ DL_DATA_ACK_IND DL_DATA_ACK_STATUS_IND
syn keyword Constant DYN_LINKBLK DYN_STREVENT DYN_QBAND DYN_SIZE
syn keyword Constant FASTBUF DYN_STREAM DYN_QUEUE DYN_MSGBLOCK DYN_MDBBLOCK
syn keyword Constant DYN_STRAPUSH DYN_DEVINFO DYN_MODINFO DYN_SYNCQ
syn keyword Constant FLUSHALL FLUSHDATA FLUSHR FLUSHW FLUSHRW FLUSHBAND
syn keyword Constant FMNAMESZ BPRI_HI BPRI_MED BPRI_LO BPRI_FT BPRI_WAITOK INFPSZ
syn keyword Constant IOCWAIT IOCWAIT_BIT RSLEEP RSLEEP_BIT WSLEEP WSLEEP_BIT
syn keyword Constant MSG_HIPRI MSG_ANY MSG_BAND MORECTL MOREDATA
syn keyword Constant N_CONN_REQ N_CONN_RES N_CONN_IND N_CONN_CON N_INFO_REQ N_INFO_ACK
syn keyword Constant N_DATACK_REQ N_DATACK_IND N_EXDATA_REQ N_EXDATA_IND
syn keyword Constant N_DISCON_REQ N_DISCON_IND N_DATA_REQ N_DATA_IND
syn keyword Constant N_OPTMGMT_REQ N_OK_ACK N_ERROR_ACK N_BIND_REQ N_BIND_ACK
syn keyword Constant N_RESET_REQ N_RESET_RES N_RESET_IND N_RESET_CON
syn keyword Constant N_UNITDATA_REQ N_UNITDATA_IND N_UDERROR_IND N_UNBIND_REQ
syn keyword Constant QB_FULL QB_WANTW QB_BACK QB_WANTR
syn keyword Constant QB_FULL_BIT QB_WANTW_BIT QB_BACK_BIT QB_WANTR_BIT
syn keyword Constant QENAB QWANTR QWANTW QFULL QREADR QUSE QNOENB QOLD QHLIST
syn keyword Constant QTOENAB QSYNCH QSAFE QWELDED QSVCBUSY QWCLOSE QPROCS QBACK
syn keyword Constant QENAB_BIT QWANTR_BIT QWANTW_BIT QFULL_BIT QREADR_BIT
syn keyword Constant QUSE_BIT QNOENB_BIT QOLD_BIT QHLIST_BIT QTOENAB_BIT
syn keyword Constant QSYNCH_BIT QSAFE_BIT QWELDED_BIT QSVCBUSY_BIT
syn keyword Constant QWCLOSE_BIT QPROCS_BIT QBACK_BIT
syn keyword Constant QHIWAT QLOWAT QMAXPSZ QMINPSZ QCOUNT QFIRST QLAST QFLAG
syn keyword Constant QNORM QPCTL
syn keyword Constant QR_DONE QR_ABSORBED QR_TRIMMED QR_LOOP QR_PASSALONG
syn keyword Constant QR_PASSFLOW QR_DISABLE QR_STRIP QR_RETRY
syn keyword Constant RMODEMASK RPROTMASK SNDZERO SNDPIPE SNDHOLD RERRNORM RERRNONPERSIST
syn keyword Constant RS_HIPRI RNORM RMSGD RMSGN RPROTDAT RPROTDIS RPROTNORM
syn keyword Constant SNDMREAD SNDMREAD_BIT STRHOLD STRHOLD_BIT STRMSIG
syn keyword Constant STRMSIG_BIT STRDELIM STRDELIM_BIT STRTOSTOP_BIT STRTOSTOP
syn keyword Constant STRPRI STRPRI_BIT STRHUP STRHUP_BIT STWOPEN STWOPEN_BIT
syn keyword Constant STRISFIFO STRISPIPE STRISFIFO_BIT STRISPIPE_BIT STRISSOCK STRISSOCK_BIT
syn keyword Constant STRCLONE STRCLONE_BIT STRNDEL STRNDEL_BIT
syn keyword Constant STRDERR_BIT STWRERR STWRERR_BIT STRCLOSE STRCLOSE_BIT
syn keyword Constant STRMOUNT_BIT STRMOUNT
syn keyword Constant PSLEEP_BIT PSLEEP
syn keyword Constant SO_ALL SO_READOPT SO_WROFF SO_MINPSZ SO_MAXPSZ SO_HIWAT SO_LOWAT SO_MREADON
syn keyword Constant SO_BAND SO_DELIM SO_NODELIM SO_STRHOLD
syn keyword Constant SO_MREADOFF SO_NDELON SO_NDELOFF SO_ISTTY SO_ISNTTY SO_TOSTOP SO_TONSTOP
syn keyword Constant SO_ERROPT SO_LOOP SO_COPYOPT SO_MAXBLK
syn keyword Constant STPLEX STPLEX_BIT STRISTTY STRISTTY_BIT STRDERR
syn keyword Constant STRHIGH STRLOW STRMAXPSZ STRMINPSZ
syn keyword Constant S_ERROR_BIT S_HANGUP_BIT S_RDNORM_BIT S_WRNORM_BIT
syn keyword Constant S_IFIFO S_ISUID S_ISGID S_ISVTX S_IRWXU S_IRUSR S_IWUSR
syn keyword Constant S_IFMT S_IFSOCK S_IFLNK S_IFREG S_IFBLK S_IFDIR S_IFCHR
syn keyword Constant S_INPUT S_HIPRI S_OUTPUT S_MSG S_ERROR S_HANGUP S_RDNORM
syn keyword Constant S_INPUT_BIT S_HIPRI_BIT S_OUTPUT_BIT S_MSG_BIT
syn keyword Constant S_IWOTH S_IXOTH S_IRWXUGO S_IALLUGO S_IRUGO S_IWUGO
syn keyword Constant S_IXUGO
syn keyword Constant S_IXUSR S_IRWXG S_IRGRP S_IWGRP S_IXGRP S_IRWXO S_IROTH
syn keyword Constant S_RDBAND_BIT S_WRBAND_BIT S_BANDURG_BIT
syn keyword Constant S_WRNORM S_RDBAND S_WRBAND S_BANDURG
syn keyword Constant TASK_INTERRUPTIBLE TASK_UNINTERRUPTIBLE TASK_RUNNING MAX_SCHEDULE_TIMEOUT
syn keyword Constant TBADADDR TBADOPT TACCES TBADF TNOADDR TOUTSTATE TBADSEQ
syn keyword Constant TNOSTRUCTYPE TBADNAME TBADQLEN TADDRBUSY TINDOUT
syn keyword Constant TNOUDERR TBADFLAG TNOREL TNOTSUPPORT TSTATECHNG
syn keyword Constant TPROVMISMATCH TRESQLEN TRESADDR TQFULL TPROTO
syn keyword Constant TSYSERR TLOOK TBADDATA TBUFOVFLW TFLOW TNODATA TNODIS
syn keyword Constant T_ADDR_ACK T_CAPABILITY_REQ T_CAPABILITY_ACK T_INFO_REQ T_INFO_ACK
syn keyword Constant T_CONN_REQ T_CONN_RES T_CONN_IND T_CONN_CON T_DATA_REQ
syn keyword Constant T_DATA_IND T_EXDATA_REQ T_EXDATA_IND T_OPTDATA_REQ T_OPTDATA_IND T_DISCON_REQ
syn keyword Constant T_DIS T_UNITDATA T_CALL T_OPTMGMT T_BIND T_UDERROR T_INFO T_ALL T_OPT T_ADDR T_UDATA
syn keyword Constant T_DISCON_IND T_ORDREL_REQ T_ORDREL_IND T_UNITDATA_REQ
syn keyword Constant T_ERROR_ACK T_OPTMGMT_REQ T_OPTMGMT_ACK T_ADDR_REQ T_UNBIND_REQ
syn keyword Constant T_UNITDATA_IND T_UDERROR_IND T_BIND_REQ T_BIND_ACK T_OK_ACK
syn keyword Constant T_YES T_NO T_INFINITE T_UNSPEC T_UNUSED T_ABSREQ T_SNDZERO T_INVALID
syn keyword Constant WERRNORM WERRNONPERSIST ANYMARK LASTMARK MUXID_ALL
syn keyword PreProc CDF_ATTACH_PENDING CDF_DETACH_PENDING
syn keyword PreProc CDF_READ_ACTIVE CDF_INPUT_ALLOWED CDF_DISABLE_PENDING CDF_OUTPUT_ACTIVE
syn keyword PreProc CDF_UNATTACHED CDF_UNUSABLE CDF_DISABLED CDF_ENABLE_PENDING CDF_ENABLED
syn keyword PreProc CDF_XRAY
syn keyword PreProc DEFINE_WAIT DECLARE_WAITQUEUE INIT_LIST_HEAD init_waitqueue_head
syn keyword PreProc prepare_to_wait prepare_to_wait_exclusive finish_wait
syn keyword PreProc current stri_lookup socki_lookup stri_acquire stri_remove
syn keyword PreProc DLF_BIND_PENDING DLF_UNBIND_PENDING DLF_IDLE DLF_UDQOS_PENDING
syn keyword PreProc DLF_DISCON12_PENDING DLF_DISCON13_PENDING DLF_SUBS_BIND_PND
syn keyword PreProc DLF_DISCON8_PENDING DLF_DISCON9_PENDING DLF_DISCON11_PENDING
syn keyword PreProc DLF_OUTCON_PENDING DLF_INCON_PENDING DLF_CONN_RES_PENDING DLF_DATAXFER
syn keyword PreProc DLF_SUBS_UNBIND_PND
syn keyword PreProc DLF_UNATTACHED DLF_ATTACH_PENDING DLF_DETACH_PENDING DLF_UNBOUND
syn keyword PreProc DLF_USER_RESET_PENDING DLF_PROV_RESET_PENDING DLF_RESET_RES_PENDING
syn keyword PreProc F_DUPFD F_GETFD F_SETFD F_GETFL F_SETFL F_GETLK F_SETLK
syn keyword PreProc F_RDLCK F_WRLCK F_UNLCK F_EXLCK F_SHLCK F_INPROGRESS
syn keyword PreProc F_SETLKW F_SETOWN F_GETOWN F_SETSIG F_GETSIG FD_CLOEXEC
syn keyword PreProc MAY_EXEC MAY_WRITE MAY_READ FMODE_READ FMODE_WRITE READ WRITE READA SPECIAL
syn keyword PreProc FNDELAY FEXCL FREAD FWRITE FCREAT FTRUNC FKLYR FSYNC FAPPEND
syn keyword PreProc MODULE_AUTHOR MODULE_DESCRIPTION MODULE_SUPPORTED_DEVICE MODULE_LICENSE
syn keyword PreProc MODULE_PARM MODULE_PARM_DESC MODULE_ALIAS
syn keyword PreProc MOD_INC_USE_COUNT THIS_MODULE MOD_DEC_USE_COUNT module_init module_exit __init __exit
syn keyword PreProc O_ACCMODE O_RDONLY O_WRONLY O_RDWR O_CREAT O_TRUNC O_EXCL
syn keyword PreProc O_DIRECTORY O_NOFOLLOW O_LARGEFILE O_DIRECT O_CLONE
syn keyword PreProc O_NOCTTY O_NONBLOCK O_APPEND O_NDELAY O_SYNC FASYNC
syn keyword PreProc O_SI_GETUDATA SI_SHUTDOWN SI_LISTEN SI_SETMYNAME
syn keyword PreProc POLLIN POLLPRI POLLOUT POLLERR POLLHUP POLLNVAL POLLRDNORM
syn keyword PreProc POLLRDBAND POLLWRNORM POLLWRBAND POLLMSG
syn keyword PreProc SI_SETPEERNAME SI_GETINTRANSIT SI_TCL_LINK SI_TCL_UNLINK
syn keyword PreProc SI_SOCKPARAMS SI_GETUDATA
syn keyword PreProc S_ISLNK S_ISREG S_ISDIR S_ISCHR S_ISBLK S_ISFIFO S_ISSOCK
syn keyword PreProc TI_ACCEPT TI_CONNECT TI_DISCONNECT
syn keyword PreProc TI_GETINFO TI_OPTMGMT TI_BIND TI_UNBIND TI_GETMYNAME
syn keyword PreProc TI_GETPEERNAME TI_SETMYNAME TI_SETPEERNAME TI_GETPROTADDR
syn keyword PreProc TS_DATA_XFER TS_WIND_ORDREL TS_WREQ_ORDREL TS_WACK_DREQ6
syn keyword PreProc TS_UNBND TS_WACK_BREQ TS_WACK_UREQ TS_IDLE TS_WACK_OPTREQ
syn keyword PreProc TS_WACK_CREQ TS_WCON_CREQ TS_WRES_CIND TS_WACK_CRES
syn keyword PreProc TS_WACK_DREQ7 TS_WACK_DREQ9 TS_WACK_DREQ10 TS_WACK_DREQ11
syn keyword Constant TSF_DATA_XFER TSF_WIND_ORDREL TSF_WREQ_ORDREL TSF_WACK_DREQ6
syn keyword Constant TSF_UNBND TSF_WACK_BREQ TSF_WACK_UREQ TSF_IDLE TSF_WACK_OPTREQ
syn keyword Constant TSF_WACK_CREQ TSF_WCON_CREQ TSF_WRES_CIND TSF_WACK_CRES
syn keyword Constant TSF_WACK_DREQ7 TSF_WACK_DREQ9 TSF_WACK_DREQ10 TSF_WACK_DREQ11
syn keyword Special TSM_WACK_DREQ TSM_LISTEN TSM_CONNECTED TSM_DISCONN TSM_INDATA TSM_OUTDATA
syn keyword PreProc T_LISTEN T_CONNECT T_DATA T_EXDATA T_DISCONNECT T_UDERR T_ORDREL T_GODATA T_GOEXDATA T_ORDRELDATA
syn keyword PreProc T_CLTS T_COTS T_COTS_ORD
syn keyword PreProc T_OPT_DATA T_OPT_FIRSTHDR T_OPT_NEXTHDR T_ALIGN T_SPACE T_LENGTH
syn keyword PreProc N_CURRENT_VERSION N_VERSION_2 N_CONN_REQ N_CONN_RES N_DISCON_REQ N_DATA_REQ
syn keyword PreProc N_EXDATA_REQ N_INFO_REQ N_BIND_REQ N_UNBIND_REQ N_UNITDATA_REQ N_OPTMGMT_REQ
syn keyword PreProc N_CONN_IND N_CONN_CON N_DISCON_IND N_DATA_IND N_EXDATA_IND N_INFO_ACK N_BIND_ACK
syn keyword PreProc N_ERROR_ACK N_OK_ACK N_UNITDATA_IND N_UDERROR_IND N_DATACK_REQ N_DATACK_IND
syn keyword PreProc N_RESET_REQ N_RESET_IND N_RESET_RES N_RESET_CON NE_BIND_REQ NE_UNBIND_REQ
syn keyword PreProc NE_OPTMGMT_REQ NE_BIND_ACK NE_ERROR_ACK NE_OK_ACK1 NE_OK_ACK2 NE_OK_ACK3
syn keyword PreProc NE_OK_ACK4 NE_CONN_REQ NE_CONN_RES NE_DISCON_REQ NE_DATA_REQ NE_EXDATA_REQ
syn keyword PreProc NE_CONN_IND NE_CONN_CON NE_DATA_IND NE_EXDATA_IND NE_DISCON_IND1 NE_DISCON_IND2
syn keyword PreProc NE_DISCON_IND3 NE_PASS_CON NE_RESET_REQ NE_RESET_RES NE_DATACK_REQ NE_DATACK_IND
syn keyword PreProc NE_RESET_IND NE_RESET_CON NE_UNITDATA_REQ NE_UNITDATA_IND NE_UDERROR_IND
syn keyword PreProc NE_NOEVENTS
syn keyword PreProc NS_UNBND NS_WACK_BREQ NS_WACK_UREQ NS_IDLE NS_WACK_OPTREQ
syn keyword PreProc NS_WACK_RRES NS_WCON_CREQ NS_WRES_CIND NS_WACK_CRES NS_DATA_XFER NS_WCON_RREQ
syn keyword PreProc NS_WRES_RIND NS_WACK_DREQ6 NS_WACK_DREQ7 NS_WACK_DREQ9 NS_WACK_DREQ10
syn keyword PreProc NS_WACK_DREQ11 NS_NOSTATES
syn keyword Constant NSF_UNBND NSF_WACK_BREQ NSF_WACK_UREQ NSF_IDLE NSF_WACK_OPTREQ
syn keyword Constant NSF_WACK_RRES NSF_WCON_CREQ NSF_WRES_CIND NSF_WACK_CRES NSF_DATA_XFER NSF_WCON_RREQ
syn keyword Constant NSF_WRES_RIND NSF_WACK_DREQ6 NSF_WACK_DREQ7 NSF_WACK_DREQ9 NSF_WACK_DREQ10
syn keyword Constant NSF_WACK_DREQ11 NSF_NOSTATES
syn keyword Special NSM_WACK_DREQ NSM_LISTEN NSM_CONNECTED NSM_DISCONN NSM_INDATA NSM_OUTDATA
syn keyword Constant NBADADDR NBADOPT NACCESS NNOADDR NOUTSTATE NBADSEQ NSYSERR NBADDATA NBADFLAG
syn keyword Constant NNOTSUPPORT NBOUND NBADQOSPARAM NBADQOSTYPE NBADTOKEN NNOPROTOID
syn keyword PreProc N_UD_UNDEFINED N_UD_TD_EXCEEDED N_UD_CONGESTION N_UD_QOS_UNAVAIL
syn keyword PreProc N_UD_LIFE_EXCEEDED N_UD_ROUTE_UNAVAIL N_UD_SEG_REQUIRED N_PROVIDER N_USER
syn keyword PreProc N_UNDEFINED N_REASON_UNDEFINED N_DISC_P N_DISC_T N_REJ_NSAP_UNKNOWN
syn keyword PreProc N_REJ_NSAP_UNREACH_P N_REJ_NSAP_UNREACH_T N_DISC_NORMAL N_DISC_ABNORMAL N_REJ_P
syn keyword PreProc N_REJ_T N_REJ_INCOMPAT_INFO N_REJ_QOS_UNAVAIL_P N_REJ_QOS_UNAVAIL_T
syn keyword PreProc N_REJ_UNSPECIFIED N_CONGESTION N_RESET_UNSPECIFIED N_USER_RESYNC REC_CONF_OPT
syn keyword PreProc EX_DATA_OPT DEFAULT_RC_SEL DEFAULT_LISTENER TOKEN_REQUEST DEFAULT_DEST N_NO_PROT
syn keyword PreProc N_PASSIVE_PROT N_ACTIVE_PROT N_ACTIVE_PASSIVE_PROT N_LEAST_EXPENSIVE
syn keyword PreProc N_QOS_CO_RANGE1 N_QOS_CO_SEL1 N_QOS_CL_RANGE1 N_QOS_CL_SEL1 N_QOS_CO_OPT_RANGE1
syn keyword PreProc N_QOS_CO_OPT_SEL1 QOS_UNKNOWN N_CONS N_CLNS N_SNICFP N_SUBNET N_MORE_DATA_FLAG
syn keyword PreProc N_RC_FLAG
syn keyword Type thru_values_t td_values_t protection_values_t priority_values_t N_qos_co_range_t
syn keyword Type N_qos_co_sel_t N_qos_cl_range_t N_qos_cl_sel_t N_qos_co_opt_range_t
syn keyword Type N_qos_co_opt_sel_t N_info_req_t N_info_ack_t N_bind_req_t N_bind_ack_t
syn keyword Type N_unbind_req_t N_optmgmt_req_t N_error_ack_t N_ok_ack_t N_conn_req_t N_conn_ind_t
syn keyword Type N_conn_res_t N_conn_con_t N_data_req_t N_data_ind_t N_datack_req_t N_datack_ind_t
syn keyword Type N_exdata_req_t N_exdata_ind_t N_reset_req_t N_reset_ind_t N_reset_res_t
syn keyword Type N_reset_con_t N_discon_req_t N_discon_ind_t N_unitdata_req_t N_unitdata_ind_t
syn keyword Type N_uderror_ind_t
syn keyword Type cd_info_req_t cd_info_ack_t cd_attach_req_t cd_detach_req_t cd_enable_req_t
syn keyword Type cd_disable_req_t cd_ok_ack_t cd_error_ack_t cd_enable_con_t cd_disable_con_t
syn keyword Type cd_error_ind_t cd_allow_input_req_t cd_read_req_t cd_unitdata_req_t
syn keyword Type cd_write_read_req_t cd_unitdata_ack_t cd_unitdata_ind_t cd_halt_input_req_t
syn keyword Type dl_info_req_t dl_info_ack_t dl_attach_req_t dl_detach_req_t dl_bind_req_t
syn keyword Type dl_bind_ack_t dl_unbind_req_t dl_subs_bind_req_t dl_subs_bind_ack_t
syn keyword Type dl_subs_unbind_req_t dl_ok_ack_t dl_error_ack_t dl_connect_req_t dl_connect_ind_t
syn keyword Type dl_connect_res_t dl_connect_con_t dl_token_req_t dl_token_ack_t dl_disconnect_req_t
syn keyword Type dl_disconnect_ind_t dl_reset_req_t dl_reset_ind_t dl_reset_res_t dl_reset_con_t
syn keyword Type dl_unitdata_req_t dl_unitdata_ind_t dl_uderror_ind_t dl_udqos_req_t
syn keyword Type dl_enabmulti_req_t dl_disabmulti_req_t dl_promiscon_req_t dl_promiscoff_req_t
syn keyword Type dl_phys_addr_req_t dl_phys_addr_ack_t dl_set_phys_addr_req_t
syn keyword Type dl_get_statistics_req_t dl_get_statistics_ack_t dl_test_req_t dl_test_ind_t
syn keyword Type dl_test_res_t dl_test_con_t dl_xid_req_t dl_xid_ind_t dl_xid_res_t dl_xid_con_t
syn keyword Type dl_data_ack_req_t dl_data_ack_ind_t dl_data_ack_status_ind_t dl_reply_req_t
syn keyword Type dl_reply_ind_t dl_reply_status_ind_t dl_reply_update_req_t
syn keyword Type dl_reply_update_status_ind_t
syn keyword PreProc VERIFY_READ VERIFY_WRITE
syn keyword PreProc WR RD SAMESTR OTHERQ _WR _RD
syn keyword PreProc _IOC_TYPE _IOC_NR _IOC_SIZE
syn keyword PreProc _SC_T_DEFAULT_DATALEN _T_DEFAULT_ADDRLEN
syn keyword PreProc _SC_T_DEFAULT_DISCLEN _SC_T_DEFAULT_OPTLEN
syn keyword PreProc _SC_T_IOV_MAX _SC_T_DEFAULT_ADDRLEN _SC_T_DEFAULT_CONNLEN
syn keyword PreProc _T_ALIGN_OFS _T_ALIGN_OFS_OFS _T_ALIGN_SIZE
syn keyword PreProc _T_DEFAULT_CONNLEN _T_DEFAULT_DISCLEN _T_DEFAULT_OPTLEN
syn keyword PreProc _T_DEFAULT_DATALEN _T_TIMEOUT _T_IOV_MAX
syn keyword PreProc _T_OPT_DATA_OFS _T_OPT_FIRSTHDR_OFS _T_OPT_NEXTHDR_OFS _T_ALIGN_OFFSET _T_ALIGN_SIZEOF _T_SPACE_SIZEOF _T_LENGTH_SIZEOF
syn keyword cStorageClass __STREAMS_EXTERN_INLINE __STRSCHD_EXTERN_INLINE __STRUTIL_EXTERN_INLINE
syn keyword cStorageClass __EXTERN __STREAMS_EXTERN __STREAMS_ENTRYP __LIS_EXTERN_INLINE
syn keyword cStorageClass __OS7_EXTERN_INLINE
syn keyword PreProc assure ensure unless trace ptrace ctrace fixme todo
syn keyword cOperator likely unlikely prefetchw prefetch __builtin_expect __builtin_prefetch
syn keyword PreProc never rare seldom usual unusual normal abnormal assert dassert
syn keyword PreProc printd swerr pswerr throwerr complain
syn keyword Special _assure _ensure _unless _trace _ptrace _ctrace _fixme _todo
syn keyword Special _likely _unlikely
syn keyword Special _never _rare _seldom _usual _unusual _normal _abnormal _assert
syn keyword Special _printd _swerr _pswerr _throwerr _complain
syn keyword Constant __assure __ensure __unless __trace __ptrace __ctrace __fixme __todo
syn keyword Constant __likely __unlikely
syn keyword Constant __never __rare __seldom __usual __unusual __normal __abnormal __assert
syn keyword Constant __printd __swerr __pswerr __throwerr __complain
syn keyword Constant xchg atomic_inc atomic_dec atomic_add atomic_sub atomic_set atomic_dec_and_test tst_bit set_bit clr_bit
syn keyword Special XCHG
syn keyword cOperator typeof
syn keyword cStorageClass BIG_STATIC BIG_STATIC_INLINE
syn keyword cStorageClass BIG_STATIC_STH BIG_STATIC_INLINE_STH
syn keyword cStorageClass BIG_STATIC_CLONE BIG_STATIC_INLINE_CLONE
syn keyword cStorageClass STATIC INLINE __inline__ __EXTERN_INLINE ____cacheline_aligned inline
syn keyword cStorageClass asmlinkage fastcall streamscall streams_fastcall streams_regparms __attribute__ __depr
syn keyword PreProc __unlikely
syn keyword Constant __hot __hot_read __hot_write __hot_put __hot_get __hot_out __hot_in streams_inline
syn keyword PreProc FASTCALL ASMLINKAGE STREAMSCALL STREAMS_FASTCALL STREAMS_REGPARMS DEPRECATED
syn keyword Type cmodsw_t fmodsw_t
syn keyword Type fd_set ino_t mode_t nlink_t off_t pid_t daddr_t key_t suseconds_t uid_t gid_t
syn keyword Type mblk_t dblk_t queue_t qband_t qpair_t tid_t toid_t bcid_t bufcall_id_t timeout_id_t frtn_t syncq_t
syn keyword Type u_int8_t u_int16_t u_int32_t u_int64_t rwlock_t wait_queue_head_t
syn keyword Type atomic_t spinlock_t rwlock_t
syn keyword Type uid16_t gid16_t old_uid_t old_gid_t loff_t u_char u_short u_int u_long unchar
syn keyword Type uint_t u_long_t u_int_t int_t u_short_t u_char_t
syn keyword Type ulong ushort uchar dev_t cred_t caddr_t size_t ssize_t uint
syn keyword Type stdata_t streamtab_t major_t minor_t modID_t
syn keyword Type dma_addr_t dma64_addr_t mm_segment_t
syn keyword Type lis_semaphore_t lis_spin_lock_t lis_rw_lock_t lis_pci_dev_t lis_atomic_t
syn keyword Type timo_fcn_t
syn keyword Type t_scalar_t t_uscalar_t
syn keyword Type np_ulong np_long np_ushort np_short
syn keyword Type dl_ulong dl_long dl_ushort dl_short
syn keyword Type cd_ulong cd_long cd_ushort cd_short
syn keyword Type klock_t
syn keyword Type msg_type_t
syn keyword Constant EPERM ENOENT ESRCH EINTR EIO ENXIO E2BIG ENOEXEC EBADF
syn keyword Constant ECHILD EAGAIN ENOMEM EACCES EFAULT ENOTBLK EBUSY EEXIST
syn keyword Constant EXDEV ENODEV ENOTDIR EISDIR EINVAL ENFILE EMFILE ENOTTY
syn keyword Constant ETXTBSY EFBIG ENOSPC ESPIPE EROFS EMLINK EPIPE EDOM
syn keyword Constant ERANGE EDEADLK ENAMETOOLONG ENOLCK ENOSYS ENOTEMPTY
syn keyword Constant ELOOP EWOULDBLOCK ENOMSG EIDRM ECHRNG EL2NSYNC EL3HLT
syn keyword Constant EL3RST ELNRNG EUNATCH ENOCSI EL2HLT EBADE EBADR EXFULL
syn keyword Constant ENOANO EBADRQC EBADSLT EDEADLOCK EBFONT ENOSTR ENODATA
syn keyword Constant ETIME ENOSR ENONET ENOPKG EREMOTE ENOLINK EADV ESRMNT
syn keyword Constant ECOMM EPROTO EMULTIHOP EDOTDOT EBADMSG EOVERFLOW
syn keyword Constant ENOTUNIQ EBADFD EREMCHG ELIBACC ELIBBAD ELIBSCN ELIBMAX
syn keyword Constant ELIBEXEC EILSEQ ERESTART ESTRPIPE EUSERS ENOTSOCK
syn keyword Constant EDESTADDRREQ EMSGSIZE EPROTOTYPE ENOPROTOOPT
syn keyword Constant EPROTONOSUPPORT ESOCKTNOSUPPORT EOPNOTSUPP EPFNOSUPPORT
syn keyword Constant EAFNOSUPPORT EADDRINUSE EADDRNOTAVAIL ENETDOWN
syn keyword Constant ENETUNREACH ENETRESET ECONNABORTED ECONNRESET ENOBUFS
syn keyword Constant EISCONN ENOTCONN ESHUTDOWN ETOOMANYREFS ETIMEDOUT
syn keyword Constant ECONNREFUSED EHOSTDOWN EHOSTUNREACH EALREADY EINPROGRESS
syn keyword Constant ESTALE EUCLEAN ENOTNAM ENAVAIL EISNAM EREMOTEIO EDQUOT
syn keyword Constant ENOMEDIUM EMEDIUMTYPE ERESTARTSYS
syn keyword Special FIOSETOWN SIOCSPGRP FIOGETOWN SIOCGPGRP SIOCATMARK SIOCGSTAMP
syn keyword PreProc ERR_PTR PTR_ERR IS_ERR
syn keyword Constant MSGDELIM MSGMARK MSGNOLOOP MSGNOGET MSGATTEN MSGMARKNEXT MSGLOG MSGNOTMARKNEXT
syn keyword Constant MSGCOMPRESS MSGNOTIFY
syn keyword Constant KM_SLEEP KM_NOSLEEP
syn keyword Constant STR_LOAD_DEV STR_UNLOAD_DEV STR_LOAD_MOD STR_UNLOAD_MOD
syn keyword Constant STR_NEW_OPEN STR_OLD_OPEN STR_QSAFETY STR_MPSAFE
syn keyword Constant STR_PERSTREAM STR_Q_NOTTOSPEC STR_64BIT STR_NEWCLONING
syn keyword Constant STR_IS_DEVICE STR_IS_MODULE STR_TYPE_MASK STR_SYSV4_OPEN
syn keyword Constant STR_QSAFETY STR_IS_SECURE
syn keyword Constant D_REOPEN D_CLONE D_FIFO D_PIPE D_SOCK D_LIS D_HEAD D_NSDEV D_SAFE D_UP D_NEW D_64BIT
syn keyword Constant D_MP D_MTPERMOD D_MTQPAIR D_MTPERQ D_MTOUTPERIM D_MTOCEXCL D_MTPUTSHARED
syn keyword Constant F_REOPEN F_CLONE F_FIFO F_PIPE F_SOCK F_LIS F_HEAD F_NSDEV F_SAFE F_UP F_NEW F_64BIT
syn keyword Constant F_MP F_MTPERMOD F_MTQPAIR F_MTPERQ F_MTOUTPERIM F_MTOCEXCL F_MTPUTSHARED
syn keyword Constant SQLVL_NOP SQLVL_QUEUE SQLVL_QUEUEPAIR SQLVL_MODULE
syn keyword Constant SQLVL_ELSEWHERE SQLVL_GLOBAL SQLVL_DEFAULT
syn keyword Constant SQLVL_PERSTREAM
syn keyword Constant SQ_OUTER SQ_INNER SQ_EXCLUS SQ_SHARED SQ_WAITERS SQ_BACKLOG SQ_SCHED
syn keyword Constant SQ_OUTER_BIT SQ_INNER_BIT SQ_EXCLUS_BIT SQ_SHARED_BIT SQ_WAITERS_BIT SQ_BACKLOG_BIT SQ_SCHED_BIT
syn keyword Constant T_ALLOPT
syn keyword Constant XTI_GENERIC XTI_DEBUG XTI_LINGER XTI_RCVBUF XTI_RCVLOWAT XTI_SNDBUF XTI_SNDLOWAT
syn keyword Constant T_INET_IP T_IP_OPTIONS T_IP_TOS T_IP_TTL T_IP_REUSEADDR T_IP_DONTROUTE T_IP_BROADCAST
syn keyword Constant T_INET_TCP T_TCP_NODELAY T_TCP_MAXSEG T_TCP_KEEPALIVE
syn keyword Constant T_TCP_CORK T_TCP_KEEPIDLE T_TCP_KEEPCNT T_TCP_SYNCNT
syn keyword Constant T_TCP_LINGER2 T_TCP_DEFER_ACCEPT T_TCP_WINDOW_CLAMP
syn keyword Constant T_TCP_QUICKACK T_TCP_INFO T_TCP_KEEPINTVL
syn keyword Constant T_INET_UDP T_UDP_CHECKSUM
syn keyword Constant T_INET_SCTP T_SCTP_NODELAY T_SCTP_MAXSEG T_SCTP_CORK T_SCTP_PPI T_SCTP_SID T_SCTP_SSN T_SCTP_TSN
syn keyword Constant T_SCTP_RECVOPT T_SCTP_COOKIE_LIFE T_SCTP_SACK_DELAY T_SCTP_PATH_MAX_RETRANS
syn keyword Constant T_SCTP_ASSOC_MAX_RETRANS T_SCTP_MAX_INIT_RETRIES T_SCTP_HEARTBEAT_ITVL T_SCTP_RTO_INITIAL
syn keyword Constant T_SCTP_RTO_MIN T_SCTP_RTO_MAX T_SCTP_OSTREAMS T_SCTP_ISTREAMS T_SCTP_COOKIE_INC
syn keyword Constant T_SCTP_THROTTLE_ITVL T_SCTP_MAC_TYPE T_SCTP_CKSUM_TYPE T_SCTP_HB T_SCTP_RTO
syn keyword Constant T_SCTP_STATUS T_SCTP_DEBUG
syn keyword Constant T_SCTP_CKSUM_TYPE T_SCTP_ECN T_SCTP_ALI T_SCTP_ADD T_SCTP_SET T_SCTP_ADD_IP
syn keyword Constant T_SCTP_DEL_IP T_SCTP_SET_IP T_SCTP_PR T_SCTP_LIFETIME T_SCTP_DISPOSITION
syn keyword Constant T_SCTP_MAX_BURST
syn keyword Constant T_NOTSUPPORT T_FAILURE T_READONLY T_PARTSUCCESS T_SUCCESS
syn keyword Constant T_CURRENT T_DEFAULT T_CHECK T_NEGOTIATE
syn keyword Constant T_ISO_TP
syn keyword Constant T_CLASS0 T_CLASS1 T_CLASS2 T_CLASS3 T_CLASS4
syn keyword Constant T_PRITOP T_PRIHIGH T_PRIMID T_PRILOW T_PRIDFLT
syn keyword Constant T_NOPROTECT T_PASSIVEPROTECT T_ACTIVEPROTECT
syn keyword Constant T_TCO_THROUGHPUT T_TCO_TRANSDEL T_TCO_RESERRORRATE T_TCO_TRANSFFAILPROB
syn keyword Constant T_TCO_ESTFAILPROB T_TCO_RELFAILPROB T_TCO_ESTDELAY T_TCO_RELDELAY
syn keyword Constant T_TCO_CONNRESIL T_TCO_PROTECTION T_TCO_PRIORITY T_TCO_EXPD
syn keyword Constant T_TCO_LTPDU T_TCO_ACKTIME T_TCO_REASTIME T_TCO_PREFCLASS T_TCO_ALTCLASS1
syn keyword Constant T_TCO_ALTCLASS2 T_TCO_ALTCLASS3 T_TCO_ALTCLASS4 T_TCO_EXTFORM T_TCO_FLOWCTRL
syn keyword Constant T_TCO_CHECKSUM T_TCO_NETEXP T_TCO_NETRECPTCF
syn keyword Constant T_TCL_TRANSDEL T_TCL_RESERRORRATE T_TCL_PROTECTION T_TCL_PRIORITY
syn keyword Constant T_TCL_CHECKSUM
syn keyword Constant _T_TPDU_SIZE_8192
syn keyword Constant _T_TPDU_SIZE_4096
syn keyword Constant _T_TPDU_SIZE_2048
syn keyword Constant _T_TPDU_SIZE_1024
syn keyword Constant _T_TPDU_SIZE_512
syn keyword Constant _T_TPDU_SIZE_256
syn keyword Constant _T_TPDU_SIZE_128
syn keyword Special  _T_F_CO_RESERVED4
syn keyword Special  _T_F_CO_RESERVED3
syn keyword Special  _T_F_CO_EXTFORM
syn keyword Special  _T_F_CO_FLOWCTRL
syn keyword Special  _T_F_AO_NBLKEXPDATA
syn keyword Special  _T_F_AO_REQUESTACK
syn keyword Special  _T_F_AO_SELECTACK
syn keyword Special  _T_F_AO_NETEXP
syn keyword Special  _T_F_AO_NETRECPTCF
syn keyword Special  _T_F_AO_CHECKSUM
syn keyword Special  _T_F_AO_EXPD
syn keyword Define _TP_MT_ED _TP_MT_EA _TP_MT_RJ _TP_MT_AK _TP_MT_ER _TP_MT_DR _TP_MT_DC _TP_MT_CC
syn keyword Define _TP_MT_CR _TP_MT_DT _TP_MT_UD
syn keyword Define _TP_PT_INVALID_TPDU _TP_PT_TPDU_SIZE _TP_PT_CGTRANSSEL _TP_PT_CDTRANSSEL
syn keyword Define _TP_PT_CHECKSUM _TP_PT_VERSION _TP_PT_PROTECTION _TP_PT_ADDOPTIONS
syn keyword Define _TP_PT_ALTCLASS _TP_PT_ACKTIME _TP_PT_RESERRORRATE _TP_PT_PRIORITY
syn keyword Define _TP_PT_TRANSDEL _TP_PT_THROUGHPUT _TP_PT_SUBSEQUENCE _TP_PT_REASTIME
syn keyword Define _TP_PT_FLOWCTLCF _TP_PT_SELECTACK _TP_PT_ED_TPDU_NR _TP_PT_DIAGNOSTIC
syn keyword Define _TP_PT_PREF_TPDU_SIZE _TP_PT_INACTTIME
syn keyword Special _T_BIT_XTI_DEBUG _T_BIT_XTI_LINGER _T_BIT_XTI_RCVBUF _T_BIT_XTI_RCVLOWAT
syn keyword Special _T_BIT_XTI_SNDBUF _T_BIT_XTI_SNDLOWAT _T_BIT_IP_OPTIONS _T_BIT_IP_TOS
syn keyword Special _T_BIT_IP_TTL _T_BIT_IP_REUSEADDR _T_BIT_IP_DONTROUTE _T_BIT_IP_BROADCAST
syn keyword Special _T_BIT_IP_PKTINFO _T_BIT_IP_RETOPTS _T_BIT_TCP_NODELAY _T_BIT_TCP_MAXSEG
syn keyword Special _T_BIT_TCP_KEEPALIVE _T_BIT_UDP_CHECKSUM _T_BIT_SCTP_NODELAY _T_BIT_SCTP_MAXSEG
syn keyword Special _T_BIT_TCP_CORK _T_BIT_TCP_KEEPIDLE _T_BIT_TCP_KEEPCNT _T_BIT_TCP_SYNCNT
syn keyword Special _T_BIT_TCP_LINGER2 _T_BIT_TCP_DEFER_ACCEPT _T_BIT_TCP_WINDOW_CLAMP
syn keyword Special _T_BIT_TCP_QUICKACK _T_BIT_TCP_INFO _T_BIT_TCP_KEEPINTVL
syn keyword Special _T_BIT_SCTP_CORK _T_BIT_SCTP_PPI _T_BIT_SCTP_SID _T_BIT_SCTP_SSN _T_BIT_SCTP_TSN
syn keyword Special _T_BIT_SCTP_RECVOPT _T_BIT_SCTP_COOKIE_LIFE _T_BIT_SCTP_SACK_DELAY
syn keyword Special _T_BIT_SCTP_PATH_MAX_RETRANS _T_BIT_SCTP_ASSOC_MAX_RETRANS
syn keyword Special _T_BIT_SCTP_MAX_INIT_RETRIES _T_BIT_SCTP_HEARTBEAT_ITVL _T_BIT_SCTP_RTO_INITIAL
syn keyword Special _T_BIT_SCTP_RTO_MIN _T_BIT_SCTP_RTO_MAX _T_BIT_SCTP_OSTREAMS
syn keyword Special _T_BIT_SCTP_ISTREAMS _T_BIT_SCTP_COOKIE_INC _T_BIT_SCTP_THROTTLE_ITVL
syn keyword Special _T_BIT_SCTP_MAC_TYPE _T_BIT_SCTP_CKSUM_TYPE _T_BIT_SCTP_HB _T_BIT_SCTP_RTO
syn keyword Special _T_BIT_SCTP_STATUS _T_BIT_SCTP_DEBUG _T_BIT_SCTP_ECN _T_BIT_SCTP_ALI
syn keyword Special _T_BIT_SCTP_ADD _T_BIT_SCTP_SET _T_BIT_SCTP_ADD_IP _T_BIT_SCTP_DEL_IP
syn keyword Special _T_BIT_SCTP_SET_IP _T_BIT_SCTP_PR _T_BIT_SCTP_LIFETIME _T_BIT_SCTP_DISPOSITION
syn keyword Special _T_BIT_SCTP_MAX_BURST
syn keyword Special _T_BIT_TCO_THROUGHPUT _T_BIT_TCO_TRANSDEL _T_BIT_TCO_RESERRORRATE
syn keyword Special _T_BIT_TCO_TRANSFFAILPROB _T_BIT_TCO_ESTFAILPROB _T_BIT_TCO_RELFAILPROB
syn keyword Special _T_BIT_TCO_ESTDELAY _T_BIT_TCO_RELDELAY _T_BIT_TCO_CONNRESIL
syn keyword Special _T_BIT_TCO_PROTECTION _T_BIT_TCO_PRIORITY _T_BIT_TCO_EXPD _T_BIT_TCO_LTPDU
syn keyword Special _T_BIT_TCO_ACKTIME _T_BIT_TCO_REASTIME _T_BIT_TCO_EXTFORM _T_BIT_TCO_FLOWCTRL
syn keyword Special _T_BIT_TCO_CHECKSUM _T_BIT_TCO_NETEXP _T_BIT_TCO_NETRECPTCF _T_BIT_TCO_PREFCLASS
syn keyword Special _T_BIT_TCO_ALTCLASS1 _T_BIT_TCO_ALTCLASS2 _T_BIT_TCO_ALTCLASS3
syn keyword Special _T_BIT_TCO_ALTCLASS4 _T_BIT_TCL_TRANSDEL _T_BIT_TCL_RESERRORRATE
syn keyword Special _T_BIT_TCL_PROTECTION _T_BIT_TCL_PRIORITY _T_BIT_TCL_CHECKSUM
syn keyword Special _T_BIT_LAST
syn keyword PreProc this_thread
syn keyword PreProc QRUNFLAG STRMFUNCS STRBCFLAG STRBCWAIT FLUSHWORK FREEBLKS STRTIMOUT STREVENTS QSYNCFLAG SCANQFLAG QWANTRUN
syn keyword Special qrunflag strmfuncs strbcflag strbcwait flushwork freeblks strtimout strevents qsyncflag scanqflag qwantrun
syn keyword PreProc current_context
syn keyword Special CTX_PROC CTX_ATOMIC CTX_STREAMS CTX_INT CTX_ISR
syn keyword PreProc POLL_IN POLL_OUT POLL_MSG POLL_ERR POLL_PRI POLL_HUP
syn keyword PreProc SI_USER SI_KERNEL SI_QUEUE SI_TIMER SI_MESGQ SI_ASYNCIO SI_SIGIO SI_TKILL SI_DETHREAD
syn keyword Special SIGABRT SIGALRM SIGBUS SIGCHLD SIGCONT SIGFPE SIGHUP SIGILL SIGINT SIGKILL
syn keyword Special SIGPIPE SIGQUIT SIGSEGV SIGSTOP SIGTERM SIGTSTP SIGTTIN SIGTTOU SIGUSR1 SIGUSR2
syn keyword Special SIGPOLL SIGPROF SIGSYS SIGTRAP SIGURG SIGVTARLM SIGXCPU SIGXFSZ
syn keyword PreProc EXPORT_SYMBOL EXPORT_SYMBOL_GPL EXPORT_SYMBOL_NOVERS FASTCALL
syn keyword Type asmlinkage
syn keyword Special INFTIM
syn keyword Constant __EVENT_EOF __EVENT_NO_MSG __EVENT_TIMEOUT __EVENT_UNKNOWN
syn keyword Constant __RESULT_DECODE_ERROR __RESULT_SCRIPT_ERROR __RESULT_INCONCLUSIVE __RESULT_FAILURE
syn keyword Special __RESULT_NOTAPPL __RESULT_SKIPPED
syn keyword PreProc __RESULT_SUCCESS
syn keyword Constant SL_ERROR SL_TRACE SL_NOTIFY SL_CONSOLE SL_FATAL SL_WARN SL_NOTE SL_NOPUTBUF
syn keyword PreProc LOGMSGSZ NLOGARGS LOGCTL
syn keyword Special I_ERRLOG I_TRCLOG I_CONSLOG
syn keyword Special LOG_EMERG LOG_ALERT LOG_CRIT LOG_ERR LOG_WARNING LOG_NOTICE LOG_INFO LOG_DEBUG
syn keyword Special SE_STREAM SE_BUFCALL SE_TIMEOUT SE_WELDQ SE_UNWELDQ
syn keyword Type qi_putp_t qi_srvp_t qi_qopen_t qi_qclose_t qi_qadmin_t
syn keyword Special ACCEPTOR_id ADDR_length ADDR_offset ADDR_size BIND_flags CAP_bits1 CDATA_size
syn keyword Special CONIND_number CONN_flags CORRECT_prim CURRENT_state DATA_flag DATA_xfer_flags
syn keyword Special DDATA_size DEST_length DEST_offset DISCON_orig DISCON_reason ENSDU_size
syn keyword Special ERROR_prim ERROR_type ETSDU_size INFO_ack LOCADDR_length LOCADDR_offset
syn keyword Special MGMT_flags MORE_flag NIDU_size NODU_size NPI_error NPI_version NSDU_size
syn keyword Special OPTIONS_flags OPT_length OPTMGMT_flags OPT_offset OPT_size PRIM_type
syn keyword Special PROTOID_length PROTOID_offset PROVIDER_flag PROVIDER_type QOS_length QOS_offset
syn keyword Special QOS_range_length QOS_range_offset REMADDR_length REMADDR_offset RESERVED_field
syn keyword Special RESET_orig RESET_reason RES_length RES_offset SEQ_number SERV_type SRC_length
syn keyword Special SRC_offset TIDU_size TLI_error TOKEN_value TSDU_size UNIX_error
syn keyword Type pl_t psw_t str_t lock_t rwlock_t socklen_t
