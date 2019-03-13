# 1 = move.pdb, 2 = stay.pdb, 3 = cut on sap res.score

home/superWrms $argv[1] $argv[2] 0.001 $argv[1]
cp $argv[2] supall.pdb
echo TER >> supall.pdb
cat rot.pdb >> supall.pdb
rasmol supall.pdb
