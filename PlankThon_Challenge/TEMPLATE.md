# Template of Hackathon Plankton Model Serving

To launch the server locally:

```console
    $ python3 -m venv env
    $ source env/bin/activate
    $ pip3 install -r requirements.txt
    $ uvicorn main:app --reload --host=127.0.0.1 --port=8080
```

To do an unit test:

```console
    $ pytest test_local_server.py
```

To launch the server in a container:

```console
    $ chmod +x ./build.sh ./run.sh
    $ ./build.sh
    $ ./run.sh
```

To read docs or try this api in your browser, please navigate to:

- openapi : <http://127.0.0.1:8080/docs#/>
- redoc : <http://127.0.0.1:8080/redoc/>
- openapi as json : <http://127.0.0.1:8080/hackathon-plankton-openapi.json>

To push your image to Docker Hub:

```console

    $ chmod +x ./push.sh
    $ ./push.sh
```

Notes:

- You should replace some codes in `main.py`, `requirements.txt`, `build.sh`, `run.sh`, `push.sh` as asked like this:

```python
### START CODE HERE (replace codes below with your codes) ###
...
...
...
### END CODE HERE ###
```

- If you use the provided baseline(model-3825702330334969856) as yours, you will be removed from the list of candidates. This baseline model just help you to understand how to serve a Tensorflow savedModel within the uvicorn server. That's all.
- Please don't be shy to ask questions to us during this competition.
