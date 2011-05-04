#!/usr/bin/env bash
#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/


# Run this script to set up development with git.

die() {
  echo 'Failure during ITK Git development setup' 1>&2
  echo '----------------------------------------' 1>&2
  echo '' 1>&2
  echo "$@" 1>&2
  exit 1
}

# Make sure we are inside the repository.
cd "$(echo "$0"|sed 's/[^/]*$//')"/..

if test -d .git/.git; then
  die "The directory '.git/.git' exists, indicating a configuration error.

Please 'rm -rf' this directory."
fi

echo "Initializing and downloading submodules..."
git submodule update --init || die "Failure downloading submodules."
echo -e "Done.\n"

# add an "upstream" remote to make easier to maintain a fork outside of itk.org,
# with an origin which is not itk.org
if [ "`git config remote.origin.url`" != "git://itk.org/ITK.git" ]; then
  echo "We advise setting git://itk.org/ITK.git as your origin.

If you choose not to do that, then other instructions will not work as expected."

  read -ep "Do you wish to continue with this non-standard layout? [y/N]: " ans

  if [ "$ans" == "" ] || [ "$ans" == "N" ] || [ "$ans" == "n" ]; then
    echo "Please fix your origin remote, and re-run this script.

Please run the following to correct the origin url:

git remote set-url origin git://itk.org/ITK.git
"
    exit 1
  else
    echo "Setting up upstream remote to the itk.org repository..."
    if ! git config remote.upstream.url > /dev/null ; then
      git remote add upstream git://itk.org/ITK.git
      git remote set-url --push upstream git@itk.org:ITK.git
      echo "Done"
    else
      echo "upstream is already configured."
    fi
    echo
    echo "WARNING: continuing with non-standard origin remote."
  fi
elif [ "`git config remote.origin.pushurl`" != "git@itk.org:ITK.git" ]; then
  echo "Setting pushurl for origin."
  git remote set-url --push origin git@itk.org:ITK.git
else
  echo "Configuration of origin verified."
fi
echo

cd Utilities/DevelopmentSetupScripts

echo "Checking basic user information..."
./SetupUser.sh || exit 1
echo

echo "Setting up git hooks..."
./SetupHooks.sh || exit 1
echo

echo "Setting up useful Git aliases..."
./SetupGitAliases.sh || exit 1
echo

# Make this non-fatal, as it is useful to get the other stuff set up
echo "Setting up Gerrit..."
./SetupGerrit.sh || echo "Gerrit setup failed, continuing. Run this again to setup Gerrit."
echo

# Make the topic stage a non-fatal error too
echo "Setting up the topic stage..."
./SetupTopicStage.sh || echo "Failed to setup topic stage. Run this again to setup stage."
echo

echo "Suggesting git tips..."
./GitTips.sh || exit 1
echo
