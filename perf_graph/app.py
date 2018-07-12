import json
import os

from flask import Flask, render_template

from helper import (calculate_average_normal, calculate_c_pressure,
                    format_data, merge_data,calculate_spark_pressure)

app = Flask(__name__)


@app.route("/")
def index():
    key = 'io_rate MB/s'
    spark_data, standard_data, c_data = calculate_average_normal(
        'spark', key), calculate_average_normal('c++', key), calculate_average_normal('standard', key)
    data = merge_data([spark_data, standard_data,c_data])
    order = ["#", "spark","c++","standard"]
    data = [ [k]+v for k,v in data.items()]
    return render_template('performance.html', data=data,order=order)

@app.route("/pressure/spark/<key>")

def pressure_spark(key):
    keymap = {
        'iorate':'io_rate MB/s',
        'iops':'iops file/s'
    }
    if key not in keymap:
        return "KEY SHOULD BE IORATE OR IOPS, INVALED KEY."
    data = calculate_spark_pressure('data/pressure/spark',keymap[key])
    return render_template("pressure.html", data=data, loader='spark')


@app.route('/pressure/c++/<key>')
def pressure_c(key):
    keymap = {
        'iorate':'io_rate MB/s',
        'iops':'iops file/s'
    }
    if key not in keymap.keys():
        return "BAD KEY, SHOULD BE iorate or iops"
    data = calculate_c_pressure('data/pressure/c++',keymap[key])
    # order seq-hdd, seq-ssd, ran-hdd, ran-ssd, std-hdd, std-ssd
    data = format_data(data)
    return render_template("pressure_c.html", data=data, loader='c++')

if __name__ == "__main__":
    app.run(host="0.0.0.0",debug=True)
