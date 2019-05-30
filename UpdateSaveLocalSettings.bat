REM Batch to checkout develop, pull from upstream, push to origin, checkout SaveLocalSettings, merge with develop, push to origin
REM DAV 30MAY2019

git.exe checkout develop --
git.exe pull -v --progress "upstream" develop
git.exe push -v --progress "origin" develop:develop
git.exe checkout SaveLocalSettings --
git.exe merge develop
git.exe push -v --progress "origin" SaveLocalSettings:SaveLocalSettings




