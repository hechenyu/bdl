import json
import os


def calculate_average_normal(loader, key):
    if loader not in ['spark', 'c++', 'standard']:
        return {}
    else:
        path = 'data/normal/'+loader
        res, json_files = {}, []
        for r, _, files in os.walk(path):
            for f in files:
                json_files.append(os.path.join(r, f))
        for f in json_files:
            with open(f) as f:
                j = json.load(f)
                # label eg: ran-ssd, ran-hdd
                label = j['label'].split(
                    '.')[2] + '-' + j['label'].split('.')[3]
                if label not in res:
                    res[label] = [j[key]]
                else:
                    res[label].append(j[key])
        res = {k: sum(v)/len(v) for k, v in res.items()}
    return res


def calculate_spark_pressure(rootdir, key):
    res = {}
    hdddir, ssddir = os.path.join(rootdir, 'hdd'), os.path.join(rootdir, 'ssd')
    for disk_type in [hdddir, ssddir]:
        resfile = []
        for r, _, files in os.walk(disk_type):
            for f in files:
                resfile.append(os.path.join(disk_type, f))
        resfile = sorted(resfile)
        for f in resfile:
            with open(f) as f:
                json_res = json.load(f)
                label = os.path.split(disk_type)[-1]
                if label not in res:
                    res[label] = [json_res[key]]
                else:
                    res[label].append(json_res[key])
    data = []
    length = len(max(res.values(), key=lambda x: len(x)))
    for i in range(0, length):
        k = [str(i+1)+'Thread']
        for key in res.keys():
            if len(res[key]) > i:
                k.append(res[key][i])
        data.append(k)

    return data



# params
'''
params:
[
    {seq:123,ran:3123},
    {seq:23,ran:31}
 ]
return:
{
    seq:[123,23]
    ran:[3123,31]
}
'''


def merge_data(data):
    keys = max(data, key=lambda x: len(x)).keys()
    res = {}
    for key in keys:
        for d in data:
            if key not in d:
                d[key] = 0

            if key not in res:
                res[key] = [d[key]]
            else:
                res[key].append(d[key])
    return res


def calculate_c_pressure(rootdir, key):
    res = {}
    res_files = []
    for read_type in os.listdir(rootdir):
        for thrednums in [1, 5, 10, 20, 30, 40]:
            # get all files of partitular thread and read_type
            res_files = []
            for r, _, files in os.walk(os.path.join(rootdir, read_type, str(thrednums))):
                for f in files:
                    res_files.append(os.path.join(r, f))
            # calculate average io_rate,iops for each file
            io = []
            for f in res_files:
                with open(f) as f:
                    lines = f.readlines()
                    jsons = [json.loads(line) for line in lines]
                    io.append(sum([x[key] for x in jsons]) / len(jsons))
            if read_type not in res:
                res[read_type] = [sum(io)]
            else:
                res[read_type].append(sum(io))
    return res


def format_data(data):
    res = []
    order = ['seq.hdd', 'seq.ssd', 'ran.hdd', 'ran.ssd', 'std.hdd', 'std.ssd']
    for i, thread in enumerate([1, 5, 10, 20, 30, 40]):
        k = [str(thread)+'Thread']
        for t in order:
            k.append(data[t][i])
        res.append(k)
    return res
def get_c_dir(rootdir):
    dirs = list(os.listdir(rootdir))
    dirs.remove('spark')
    return dirs