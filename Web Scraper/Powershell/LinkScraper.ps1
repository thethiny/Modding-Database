MKDIR "output" 2>$NULL
$prefix = "https://www.alarabiya.net/ar/archive.news.html?currentPage="
$string = "/ar/"
$string2 = "html"
for ($url = 1; $url -le 3506; $url++)
{
	$site = curl ($prefix + $url) -UseBasicParsing
	foreach ($link in $site.links.href)
	{
		if ($link.length -ge 4)
		{
			if ( $string -eq ($link[0]+$link[1]+$link[2]+$link[3]))
			{
				if ($string2 -eq ($link[$link.length-4] + $link[$link.length-3] +$link[$link.length-2] +$link[$link.length-1]))
				{
					$link | Out-File "output\LinksFromArchive.txt" -append -Encoding UTF8
				}
			}
		}
	}
}