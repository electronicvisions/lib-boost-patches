#!/usr/bin/env python
import sys, os

def depends(ctx):
    ctx('lib-boost-patches', 'test')

def options(opt):
    opt.load('gxx')
    opt.load('boost')


def configure(cfg):
    cfg.check_waf_version(mini='1.6.10')
    cfg.load('gxx')
    cfg.load('boost')

    cfg.check_boost(lib='serialization', uselib_store='BOOST_SERIALIZATION_')


def build(bld):
    bld (
            target          = 'boost_serialization',
            use             = ['BOOST_SERIALIZATION_'],
            export_includes = '.',
    )

    bld (
            target          = 'boost_patches',
            use             = ['BOOST_SERIALIZATION_'],
            export_includes = '.',
    )
