MKDIR "output" 2>$NULL
MKDIR "output\mini" 2>$NULL
$prefix = "https://www.alarabiya.net/ar/archive.news.html?currentPage="
$string = "/ar/"
$string2 = "html"
for ($url = 1; $url -le 3506; $url++)
{
	$site = curl ($prefix + $url)
	foreach ($element in $site.parsedHTML.getElementsByTagName("p"))
	{
		$element.innerText | Out-File "output\mini\$url.txt" -append
	}
	echo $url
}