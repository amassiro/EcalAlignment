########
# 25 ns
########
#        CRAB task name          DAS name                                                                                                              
samples['25ns_DYJetsToEE']   = ['/DYToEE_NNPDF30_13TeV-powheg-pythia8/RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016_v3-v1/MINIAODSIM',  ['outputFile=treeECALAlignment.root']]

# hadd /tmp/amassiro/ECAL_DYMC.root /tmp/amassiro/eos/cms/store/group/dpg_ecal/alca_ecalcalib/amassiro/ECALAlignment/MC07May2016/DYToEE_NNPDF30_13TeV-powheg-pythia8/crab_25ns_DYJetsToEE/160507_135010/0000/tr*.root



########
# Alternative global configuration
########

config.JobType.maxMemoryMB = 2500    # 2.5 GB
config.JobType.psetName = '../Dump_MC_cfg.py'
config.Data.outLFNDirBase = '/store/group/dpg_ecal/alca_ecalcalib/amassiro/ECALAlignment/MC07May2016'


config.General.workArea     = 'crab_projects_07May'