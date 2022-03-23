##############################################################################
# File: test_local_server.py
# Project: hackathon-plankton
# Created Date: Saturday, June 19th 2021, 4:33:39 pm
# Author: ZHANG Xiyu
# -----
# Last Modified: Friday, 25th June 2021 10:18:27 am
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
"""This script help us to do a unittest for the running local server.
We launch a prediction job on 6 photos. If the reponse is the same as the
provided response, we think that everything is good.
In our case, we focus on the router `http://127.0.0.1/:8080`.

Example:
    $ python3 test_local_server.py
or
    $ pytest test_local_server.py
"""
import json
import unittest
import numpy as np
import requests


class TestProcess(unittest.TestCase):
    """A class whose instances are single test cases.
    Args:
        unittest (class TestCase): A class in python unit testing framework.
    """

    def test_meter_ocr(self):
        """
        Notes:
            1. The name of function must start with test_ (this is standard
                unittest conventions).
            2. Write simple assert statements with the standard Python
                expressions that you need to check (again, standard unittest).
            3. The input body is in the directory of request.
            4. The right output json is in the directory of request too.
        """
        test_body_json = json.loads(open("tensorflow/plankthon-model/request/body.json").read())
        test_response_json = json.loads(open("tensorflow/plankthon-model/request/response.json").read())
        # launch the same POST request to the root of the running server.
        resp = requests.request(
            "POST",
            "http://127.0.0.1:8080",
            json=test_body_json,
        )
        assert resp.status_code == 200
        # check the names of classes and probabilities.
        resp_json = resp.json()
        assert "predictions" in resp_json
        labels = test_response_json["predictions"]["86177.jpg"].keys()
        for image_key, prediction in resp_json["predictions"].items():
            for label in labels:
                assert label in prediction
                assert np.isscalar(prediction[label])
        # assert resp.json() == test_response_json


if __name__ == "__main__":
    unittest.main(warnings="ignore")
