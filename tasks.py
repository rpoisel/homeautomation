#!/usr/bin/env python
# -*- coding: utf-8 -*-

import click
from invoke import Collection, Config, Exit, task
from invoke.executor import Executor
from pathlib import Path
import shutil

BUILD_DIR_BASE = '/tmp/build.homeautomation.'


def __get_build_dir(target):
    return Path(BUILD_DIR_BASE + target).resolve()


@task
def clean(ctx, build_dir):
    shutil.rmtree(str(build_dir))


@task
def init(ctx, build_dir):
    build_dir.mkdir(parents=True, exist_ok=True)


@task
def build(ctx, build_type='Debug'):
    source_dir = str(Path(__file__).parents[0].resolve())
    build_dir = __get_build_dir('linux-arm11')

    executor = Executor(TASKS, CONFIG)
    executor.execute(
        ('init', {'build_dir': build_dir})
    )

    toolchain_file = str(
        Path(source_dir, 'build-scripts', 'cmake', 'toolchain',
             'toolchain.linux-arm11.cmake').resolve())
    with ctx.cd(str(build_dir)):
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


@task
def test(ctx):
    source_dir = str(Path(__file__).parents[0].resolve())
    build_dir = __get_build_dir('test')
    executor = Executor(TASKS, CONFIG)
    executor.execute(
        ('init', {'build_dir': build_dir})
    )

    with ctx.cd(str(build_dir)):
        ctx.run("cmake \
            -GNinja \
            -DCMAKE_BUILD_TYPE=Debug {}\
            -DBUILD_TARGET=test".format(source_dir))
        ctx.run("ninja -v")
        ctx.run("ctest --verbose --timeout 30")


TASKS = Collection(clean, init, build, test)
CONFIG = Config(defaults={"run": {"pyt": True}})
TASKS.configure(CONFIG)
