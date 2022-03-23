##############################################################################
# File: build.sh
# Project: hackathon-plankton
# Created Date: Friday, June 18th 2021, 10:33:29 pm
# Author: ZHANG Xiyu
# -----
# Last Modified: Saturday, 19th June 2021 4:31:27 pm
# Modified By: ZHANG Xiyu
# -----
# Copyright (c) 2021 Veolia S.A.
# Please add license text here.
# Nope...we're doomed!
# -----
# HISTORY:
# Date      	By	Comments
# ----------	---	----------------------------------------------------------
##############################################################################
### START CODE HERE (replace codes below with your codes) ###
# Replace `zacharietimothee/hackathon-plankton-server`
# by `your username/your repository:your tag` on Docker Hub.

function curl_and_unzip()
{
  local zipfile="tensorflow/$1.zip"

  if test -f "$zipfile"; then
    echo "$1 already exists"
  else
    curl "https://storage.googleapis.com/gbl-ist-ve-hackathon-train/$1.zip" --output tensorflow/$1.zip
    unzip tensorflow/$1.zip -d tensorflow/$1
  fi
}

# retrieve and unpack zip train files
curl_and_unzip "train"
curl_and_unzip "test"



docker build -t jessevdwolf/hackathon-plankton-server:latest .
### END CODE HERE ###
