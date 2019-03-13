# 1 = move.pdb, 2 = stay.pdb, 3 = cut on sap res.score

grep ' A ' $argv[1] > move.tmp
grep ' A ' $argv[2] > stay.tmp
home/sap $argv[1] $argv[2] | tail -1
grep ' B ' super.pdb | cut -c 61-99 > move.sap
grep ' A ' super.pdb | cut -c 61-99 > stay.sap
set cut = `cat move.sap stay.sap | awk '{s+=$1; n++; print 2*s/n}' | tail -1`
if ( $#argv > 2 ) then
	echo using given cutoff
	set sapcut = $argv[3]
else
	echo using average cutoff
	set sapcut = $cut
endif
cat move.tmp | grep ' CA ' | cut -c  1-60 > move.cas
cat stay.tmp | grep ' CA ' | cut -c  1-60 > stay.cas
paste -d '' move.cas move.sap > move.tmp
paste -d '' stay.cas stay.sap > stay.tmp
home/superWrms move.tmp stay.tmp $sapcut $argv[1]
cp $argv[2] supall.pdb
echo TER >> supall.pdb
cat rot.pdb >> supall.pdb
rasmol supall.pdb
