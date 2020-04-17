#!/usr/bin/env python
# -*- coding: utf-8 -*-

import click
from invoke import Collection, Config, Exit, task
from pathlib import Path
import shutil

BUILD_DIR = '/tmp/build.homeautomation.linux-arm11'


@task
def clean(ctx):
    shutil.rmtree(BUILD_DIR)


@task
def init(ctx):
    Path(BUILD_DIR).mkdir(parents=True, exist_ok=True)


@task(pre=[init])
def build(ctx, build_type='Debug'):
    source_dir = str(Path(__file__).parents[0].resolve())
    toolchain_file = str(
        Path(source_dir, 'build-scripts', 'cmake', 'toolchain',
             'toolchain.linux-arm11.cmake').resolve())
    with ctx.cd(BUILD_DIR):
        with click.progressbar(length=100, label='Build') as bar:
            ctx.run("conan install {} -pr=raspberry-gcc-8".format(source_dir))
            bar.update(10)
            ctx.run("cmake \
                            -GNinja \
                            -DCMAKE_BUILD_TYPE={} \
                            -DCMAKE_TOOLCHAIN_FILE={} \
                            -DCMAKE_EXPORT_COMPILE_COMMANDS=ON {}".format(
                build_type, toolchain_file, source_dir))
            bar.update(50)
            ctx.run("ninja -v docker")
            bar.update(100)


ns = Collection(clean, init, build)
config = Config(defaults={"run": {"pyt": True}})
ns.configure(config)
