#!/usr/bin/env python
import sys, os

def depends(ctx):
    ctx('lib-boost-patches', 'test')

def options(opt):
    opt.load('compiler_cxx')
    opt.load('boost')


def configure(cfg):
    cfg.check_waf_version(mini='1.6.10')
    cfg.load('compiler_cxx')
    cfg.load('boost')

    cfg.check_boost(lib='serialization', uselib_store='BOOST_SERIALIZATION_')
    cfg.check_boost(stlib='serialization', uselib_store='BOOST_SERIALIZATION_STATIC_')


def build(bld):
    bld.install_files(
        dest = '${PREFIX}/include',
        files = bld.path.ant_glob('boost/**/*.(h)'),
        name = 'boost_header',
        relative_trick = True
    )

    bld (
            target          = 'boost_serialization_inc',
            export_includes = '.',
            depends_on = 'boost_header'
    )

    bld (
            target          = 'boost_serialization',
            use             = ['BOOST_SERIALIZATION_'],
            export_includes = '.',
            depends_on = 'boost_header'
    )

    bld (
            target          = 'boost_serialization_static',
            use             = ['BOOST_SERIALIZATION_STATIC_'],
            export_includes = '.',
            depends_on = 'boost_header'
    )

    bld (
            target          = 'boost_patches',
            use             = ['BOOST_SERIALIZATION_'],
            export_includes = '.',
            depends_on = 'boost_header'
    )
