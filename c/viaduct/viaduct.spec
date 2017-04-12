# Note that this is NOT a relocatable package
%define ver      0.11.1
%define rel      1
%define prefix   /usr/local

Summary: Viaduct Program Bridge.
Name: viaduct
Version: %ver
Release: %rel
Copyright: GPL
Group: Network/
Source: http://www.rphh.org/download/viaduct-%{ver}.tar.gz
BuildRoot: /tmp/viaduct-%{ver}-root
Packager: Daniel Crompton <redhat@rphh.org>
URL: http://www.rphh.org/viaduct/

Docdir: %{prefix}/doc

%description
Viaduct is a powerful program aimed at being more than a
netcat like bridge. Besides from containing much of the
same functionality it also gives you the ability to bridge
anything to anything.

Think about it, how about linking a local mic to a remote
speaker. Or, with the soon to be added kernel module,
providing unix sockets/FIFO's/character devices/block devices
over a network connection.

Why? Because you now can!

%changelog

%prep
%setup

%build
# Optimize that damned code all the way
if [ ! -z "`echo -n ${RPM_OPT_FLAGS} | grep pentium`" ]; then
  if [ ! -z "`which egcs`" ]; then
    CC="egcs" 
  else
    if [ ! -z "`which pgcc`" ]; then
      CC="pgcc"
    fi
  fi
  CFLAGS="${RPM_OPT_FLAGS}"
else
  CFLAGS="${RPM_OPT_FLAGS}"
fi
if [ ! -f configure ]; then
  CFLAGS="$RPM_OPT_FLAGS" ./autogen.sh --prefix=%prefix
else
  CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%prefix
fi
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install

%clean
rm -rf $RPM_BUILD_ROOT

%post

%postun

%files
%defattr(-, root, root)

%{prefix}/bin/viaduct
%{prefix}/man/man1/viaduct.1.bz2

#%doc docs/ethertap.html
#%doc docs/plaap.ps
#%doc docs/viaduct.1.ps
%doc AUTHORS
%doc COPYING
%doc INSTALL
%doc README
%doc TODO
