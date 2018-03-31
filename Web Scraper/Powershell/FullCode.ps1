Function Remove-InvalidFileNameChars {
  param(
    [Parameter(Mandatory=$true,
      Position=0,
      ValueFromPipeline=$true,
      ValueFromPipelineByPropertyName=$true)]
    [String]$Name
  )

  $invalidChars = [IO.Path]::GetInvalidFileNameChars() -join ''
  $re = "[{0}]" -f [RegEx]::Escape($invalidChars)
  return ($Name -replace $re)
}

$linksArray = New-Object System.Collections.ArrayList
$prefix = "https://www.alarabiya.net"
$url = "/ar/arab-and-world/"
$site = curl ($prefix + $url)
$string = "/ar/"
$string2 = "html"
foreach ($link in $site.links.href)
{
	if ($link.length -ge 4)
	{
		if ( $string -eq ($link[0]+$link[1]+$link[2]+$link[3]) )
		{
			if ($string2 -eq ($link[$link.length-4] + $link[$link.length-3] +$link[$link.length-2] +$link[$link.length-1]))
			{
				$linksArray += $link
			}
		}
	}
}

$linksArray = $linksArray | select -uniq

DEL "output\AllFiles.txt" 2>$NULL
foreach ($url in $linksArray)
{
	$site = (curl ($prefix + $url))
	
	#Copied Seciont
	foreach ($link in $site.links.href)
	{
		if ($link.length -ge 4)
		{
			if ( $string -eq ($link[0]+$link[1]+$link[2]+$link[3]) )
			{
				if ($string2 -eq ($link[$link.length-4] + $link[$link.length-3] +$link[$link.length-2] +$link[$link.length-1]))
				{
					$linksArray += $link
				}
			}
		}
	}
	$linksArray = $linksArray | select -uniq
	#End of Copied Section

	#$temp = $site.parsedHTML.getElementsByClassName("breadcrumbs")
	#$category = Remove-InvalidFileNameChars($temp)
	#$temp = $temp[0].innerText
	#$temp =  $temp[13..($temp.length-1)]
	#$category = ""
	#foreach ($char in $temp)
	#{
	#	$category += $char
	#}
	$category = $url[4] + $url[5] + $url[6] + $url[7] + $url[8] #NEW
	$category = Remove-InvalidFileNameChars($category) #NEW
	$file = "output\$category\"
	echo $file
	(MKDIR "$file") 2> $NULL
	foreach ($title in $site.parsedHTML.getElementsByClassName("highline"))
	{
		$name = Remove-InvalidFileNameChars($title.textContent)
		$file += $name
		$file | Out-File "output\AllFiles.txt" -Encoding UTF8 -append
		echo title | Out-File "$file.txt" -Encoding UTF8
		$title.textContent | Out-File "$file.txt" -Encoding UTF8 -append
		break
	}
	echo "Source" | Out-File "$file.txt" -Encoding UTF8 -append
	foreach ($source in $site.parsedHTML.getElementsByClassName("source"))
	{
		$source.textContent | Out-File "$file.txt" -Encoding UTF8 -append
	}
	echo source
	echo "Body Text" | Out-File "$file.txt" -Encoding UTF8 -append
	foreach ($element in $site.parsedHTML.getElementsByClassName("article-body"))
	{
		$element.innerText | Out-File "$file.txt" -Encoding UTF8 -append
	}
	echo $url
	echo " "
	
}