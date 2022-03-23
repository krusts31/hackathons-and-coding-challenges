##############################################################################
# File: cleanup.sh
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
# Remove all images and containers
# Kill all running containers
sudo docker kill $(sudo docker ps -q)
# Delete all containers
sudo docker rm $(sudo docker ps -a -q)
# Delete all images
sudo docker rmi $(sudo docker images -q)
