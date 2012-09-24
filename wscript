#!/usr/bin/env python
import sys, os

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
            target          = 'boost_serialization_addons',
            use             = ['BOOST_SERIALIZATION_'],
            export_includes = '..',
    )
