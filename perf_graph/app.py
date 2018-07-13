import json
import os
import sqlite3
import time

from flask import Flask, render_template, request
from helper import (calculate_average_normal, calculate_c_pressure,
                    format_data, merge_data, calculate_spark_pressure,get_c_dir)

app = Flask(__name__)


@app.before_first_request
def init_db():
    from database import conn


@app.route("/")
def index():
    order = ["#", "spark", "c++", "standard"]
    timestamp = request.args.get('timestamp', '')
    if timestamp:
        data = sql_query(timestamp)
        timestamp = sql_timestamp('performance')
        return render_template('performance.html', data=data, order=order, timestamp=timestamp)
    key = 'io_rate MB/s'
    spark_data, standard_data, c_data = calculate_average_normal(
        'spark', key), calculate_average_normal('c++', key), calculate_average_normal('standard', key)
    data = merge_data([spark_data, standard_data, c_data])

    data = [[k]+v for k, v in data.items()]
    sql_cache("performance", json.dumps(data))
    timestamp = sql_timestamp('performance')
    return render_template('performance.html', data=data, order=order, timestamp=timestamp)


@app.route("/pressure/spark/<key>")
def pressure_spark(key):
    timestamp = request.args.get('timestamp', '')
    keymap = {
        'iorate': 'io_rate MB/s',
        'iops': 'iops file/s'
    }
    if key not in keymap:
        return "KEY SHOULD BE IORATE OR IOPS, INVALED KEY."
    if timestamp:
        data = sql_query(timestamp,key)
        timestamp = sql_timestamp('spark', key)
        return render_template('pressure.html', data=data, loader='spark', timestamp=timestamp)
    data = calculate_spark_pressure('data/pressure/spark', keymap[key])
    sql_cache("spark", json.dumps(data), key)
    timestamp = sql_timestamp('spark', key)
    return render_template("pressure.html", data=data, loader='spark', timestamp=timestamp)


@app.route('/pressure/<dir>/<key>')
def pressure_c(dir,key):
    timestamp = request.args.get('timestamp', '')
    keymap = {
        'iorate': 'io_rate MB/s',
        'iops': 'iops file/s'
    }
    if key not in keymap.keys():
        return "BAD KEY, SHOULD BE iorate or iops"

    dirs = get_c_dir('data/pressure')
    if dir not in dirs:
        return "Invalid dir path, select in" + str(dirs)
    if timestamp:
        data = sql_query(timestamp,key+dir)
        timestamp = sql_timestamp('cplus', key+dir)
        return render_template('pressure_c.html', data=data, timestamp=timestamp, loader='c++',dirs=dirs)
    data = calculate_c_pressure('data/pressure/'+dir, keymap[key])
    # order seq-hdd, seq-ssd, ran-hdd, ran-ssd, std-hdd, std-ssd
    data = format_data(data)
    sql_cache("cplus", json.dumps(data), key+dir)
    timestamp = sql_timestamp('cplus', key+dir)
    return render_template("pressure_c.html", data=data, loader='c++', timestamp=timestamp, dirs = dirs)


def sql_cache(datatype, data, key=""):
    conn = sqlite3.connect("metrics.db")
    c = conn.cursor()
    performance = c.execute(
        "SELECT * FROM performance where datatype=? AND KEY=? ", (datatype, key))
    cache_str = ""
    for i in performance:
        cache_str = i[1]
    if cache_str != data:
        c.execute('insert into performance(data,datatype,key,timestamp) values (?,?,?,?)',
                  (data, datatype, key, str(time.time())))
        conn.commit()


def sql_query(timestamp, key=""):
    conn = sqlite3.connect("metrics.db")
    c = conn.cursor()
    res = ""
    data = c.execute(
        "SELECT * FROM PERFORMANCE WHERE TIMESTAMP=? and KEY=?", (timestamp,key))
    for i in data:
        res = json.loads(i[1])
    return res


def sql_timestamp(datatype, key=""):
    conn = sqlite3.connect('metrics.db')
    c = conn.cursor()
    times = c.execute(
        'select timestamp from performance where datatype=? and key=?', (datatype, key))
    res = []
    for i in times:
        res.append(i[0])
    return res


if __name__ == "__main__":

    app.run(host="0.0.0.0", debug=True)
