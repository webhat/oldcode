# Note that this is NOT a relocatable package
%define ver      0.9.6
%define rel      1
%define prefix   /usr/local

Summary: PFunctions
Name: pfunc
Version: %ver
Release: %rel
Copyright: GPL
Group: Utilities
Source: http://www.rphh.org/download/pfunc-%{ver}.tar.gz
BuildRoot: /tmp/pfunc-%{ver}-root
Packager: Daniel Crompton <redhat@rphh.org>
URL: http://www.rphh.org/pfunc/

Docdir: %{prefix}/doc

%description
Wow, pkill and pgrep for linux...

%changelog

%prep
%setup

%build
if [ ! -z "`which egcs`" ]; then
  CC="egcs" 
else
  if [ ! -z "`which pgcc`" ]; then
    CC="pgcc"
  fi
fi
if [ ! -f configure ]; then
  ./autogen.sh --prefix=%prefix
else
  ./configure --prefix=%prefix
fi
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install

%clean
#rm -rf $RPM_BUILD_ROOT

%post

%postun

%files
%defattr(-, root, root)

%doc AUTHORS
%doc COPYING
%doc INSTALL
%doc README
%doc TODO
%{prefix}/bin/pgrep
%{prefix}/bin/pkill


