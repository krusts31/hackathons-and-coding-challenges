import os
import json
import base64
import pathlib
import zipfile
import datetime
import pandas as pd
import requests as re
import streamlit as st
import SessionState

CONST_POST_BATCHSIZE = 100
CONST_API_URL = 'http://localhost:8080'

st.title("Planktoscope data visualisation")

session = SessionState.get(name='', lon='', lat='', button=None)
if len(session.name) == 0:
    with st.form(key='station_form'):
        session.name = st.text_input(label='Station name')
        session.lon = st.text_input(label='Longitude')
        session.lat = st.text_input(label='Latitude')
        session.submit_button = st.form_submit_button(label='Submit')
    try:
        lon = float(lon)
        lat = float(lat)
        if not name:
            raise ValueError
    except Exception:
        st.warning('Please input a name, longitude and latitude')
else:
    st.write(f"""
    Creating data dashboard for station {session.name}
    at location [{session.lon},{session.lat}]
    
    # Dashboard
    """)
    
    # upload zip file
    # Display a file uploader widget. By default, uploaded files are limited to 200MB. You can configure this using the server.maxUploadSize config option.
    sample_zip_file = st.file_uploader('Upload sample.zip here', type=['zip'])
    if sample_zip_file is not None:
        
        # extract all images into the data folder
        with zipfile.ZipFile(sample_zip_file, "r") as ref:
            path = pathlib.Path(__file__).parent.resolve()
            data_dir = os.path.join(path, 'data', session.name)
            if not os.path.exists(data_dir):
                pathlib.Path(data_dir).mkdir(parents=True, exist_ok=True)
            dir_name = f"{session.name}-{datetime.datetime.now().strftime('%d-%m-%Y %H:%M:%S')}"
            ref.extractall(os.path.join(data_dir, dir_name))
    
        # convert the images to base64 encoded strings to send them to the API
        images = {}
        image_dir = os.path.join(data_dir, dir_name, 'images')
        for idx, filename in enumerate(os.listdir(image_dir)):
            if filename.endswith(".jpg"):
                with open(os.path.join(image_dir, filename), mode='rb') as f:
                    b64str = base64.b64encode(f.read())
                    images.update({filename: b64str.decode('utf-8')})

                    # send the data in batches, also to preverse RAM memory
                    if len(images) == CONST_POST_BATCHSIZE or idx == len(os.listdir(image_dir)) -1:
                        resp = re.post(CONST_API_URL, json={'images': images})
                        json_data = resp.json()
                        st.write(json.dumps(json_data))
                        images.clear()
            else:
                continue
    
        # build up the dashboard using the predictions from the model
        
    