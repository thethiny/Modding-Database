Function makeValid {
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

$domain = "https://www.alarabiya.net"
$file = Get-Content "OrgLinks.txt"
$ctr = 0
$lines = $file.count
foreach ($link in $file)
{
	echo "==============="
	$ctr++
	echo "$ctr/$lines"
	$name = "output\"
	MKDIR $name 2>$NULL
	echo "Scraping $domain$link..."
	$site = ""
	$site = curl ($domain + $link)
	echo "Parsing..."
	
	$category = ""
	$category = $site.parsedHTML.getElementsByClassName("breadcrumbs")
	$string = ""
	foreach ($char in ($category[0].innerText -replace "»", "\").split(''))
	{
		$string += $char
	}
	$name += $string + "\"
	MKDIR $name 2>$NULL
	echo "Category Scraped $string"
	
	$title = ""
	$title = $site.parsedHTML.getElementsByClassName("highline")
	$title = $title[0].textContent
	$title = makeValid($title)
	$name += $title + ".txt"
	echo "Title $title"
	echo "Title" "$title" | Out-File "$name" -Encoding UTF8 -append
	
	$source = ""
	$source = $site.parsedHTML.getElementsByClassName("source")
	$source = $source[0].textContent
	echo "Source $source"
	echo "Source" "$source" | Out-File "$name" -Encoding UTF8 -append
	
	echo "Body" | Out-File "$name" -Encoding UTF8 -append
	foreach ($element in $site.parsedHTML.getElementsByClassName("article-body"))
	{
		$element.innerText | Out-File "$name" -Encoding UTF8 -append
	}
	echo "Body Scraped into $name"
	echo " "	
	
}