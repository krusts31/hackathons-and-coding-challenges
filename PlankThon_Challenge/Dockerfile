##############################################################################
# File: Dockerfile
# Project: hackathon-plankton
# Created Date: Wednesday, June 9th 2021, 7:16:58 pm
# Author: ZHANG Xiyu
# -----
# Last Modified: Friday, 18th June 2021 2:49:49 pm
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

# Use the official lightweight Python image: https://hub.docker.com/_/python.
FROM python:3.7.10-slim

# # Use lightweight Python image for raspberry pi: https://hub.docker.com/r/arm32v7/python/.
# FROM arm32v7/python

# Set the environment variable key to the value value.
ENV APP_HOME /server

# Set the working directory for any subsequent ADD, COPY, CMD, ENTRYPOINT,
# or RUN instructions that follow it in the Dockerfile.
WORKDIR $APP_HOME

# Copy files or folders from source to the dest path in the image's filesystem.
COPY . ./

# Install production dependencies(as same as dev's dependencies).
RUN pip install -r requirements.txt

# Use it by default.
EXPOSE 8080

# The main purpose of a CMD is to provide defaults for an executing container.
CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8080"]