P0267 Reference Implementation
=============

Please read the [LICENSE](https://github.com/mikebmcl/N3888_RefImpl/blob/master/LICENSE.md) before cloning or forking the code as there is important information there!

Please see the [wiki](https://github.com/mikebmcl/N3888_RefImpl/wiki) for links to forks which provide alternate implementations!

Overview
-------------

This is a reference implementations of [P0267: A Proposal to Add 2D Rendering and Display to C++](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0267r2.pdf).

Requirements
-------------

For Windows platforms, it currently requires Visual Studio 2015 (the free Community edition should suffice) and Windows Vista or newer. 
PLEASE NOTE: In the near future this project will require Visual Studio 2017 (currently available as an RC as of 2017-01-11) in order to use C++ language and library features that are only available in that version.

For GNU/Linux platforms, it currently requires a non-ancient version of GNU autotools, cairo (>= 1.12.16), GTK+3.0 (>= 3.8.0), gmodule-2.0, gobject-2.0, and related libraries (autotools will tell you about any missing dependencies). By default it builds using GCC (>= 4.9.0), but you can configure it to use recent versions of Clang.

Feedback
-------------
If you have found a bug in the reference implementation or have a suggestion for improving P0267 please read the following. Note that any contributions must comply with the ISO patent and copyright policy, an overview of which is available in the ISO document [Participating in International Standardization](http://www.iso.org/iso/joining_in_2012.pdf).

* If you want to suggest a change to P0267 please file an [issue](https://github.com/mikebmcl/N3888_RefImpl/issues) with the tag [enhancement](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=enhancement&page=1&state=open). We will consider these for future revisions of N4073. Pull requests for suggested changes will not be accepted because this is a reference implementation.
* If you have found a bug in the reference implementation, please file an issue with the tag [bug](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=bug&page=1&state=open). Pull requests that fix bugs are welcome.
* If you have found any sort of error in P0267 (be it a typo, an omission, a contradiction, or some other non-subjective problem), please file an issue with the tag [proposal-bug](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=proposal-bug&page=1&state=open). We will do our best to address these in the next revision of P0267.
* If you have created a reference implementation for another platform or tool-chain, please let us know. We welcome these types of pull requests provided that the implementation conforms to N4073 and the licensing terms are acceptable.

The master branch is intended to reflect the most recent revision of P0267.

Licenses and Contributions (Important!)
-------------

**LICENSE CHANGE: As of 2017-01-12 01:00.00 UTC, this software is licensed under the terms of the [Boost Software License - Version 1.0](http://www.boost.org/LICENSE_1_0.txt). This does not affect any fork, clone, or download of this software, collectively a "Copy", made prior to the above-specified date and time provided that such Copy is not updated to include any changes made at or after the above-specified date and time. Any such update shall be deemed an acceptance of a license of this software solely under the terms of the Boost Software License - Version 1.0.**

Any code that you offer as a pull request must be your own work. If your employer or institution has a moonlighting policy, the act of offering a pull request shall be considered a declaration that you complied with the terms of that policy and are free to make the contribution or that your employer or institution has expressly waived any IP rights it or they might have had in your contribution thus freeing you to make the contribution.

If your contribution makes use of third party libraries it must comply with the licensing terms of those libraries. If the library is licensed under multiple licenses you must indicate which license your contribution is using ("whichever" is not acceptable). The terms of those licenses must be compatible with the terms of the licenses of any existing code. Code licensed under any version of the GPL will not be considered. (Note: LGPL code will be considered, though licenses that give more freedom to other developers are preferred.)

Any contribution shall be deemed to be made pursuant to the terms of the Boost Software License - Version 1.0, without regard to any attempt, whether by statement, inclusion of a license file, inclusion of license terms within any file, or any other method, to impose any other license.

If your code is a derivative work of the reference implementation it must be licensed under the terms of the Boost Software License - Version 1.0 unless you obtain an express, written waiver from the original author of the reference implementation, Michael B. McLaughlin. (Literally written, as in fixed on paper, signed, and physically mailed to you), except as provided above.

**If you fail to comply with the terms of any employer or institutional policies, the terms of any licenses, or if you infringe upon any patents, violate any trade secrets, violate any laws or regulations, or, by any act or omission, cause any legal action to be brought against the authors of P0267, its previous versions, the ISO C++ committee (ISO/IEC JTC1/SC22/WG21) or any of its members individually, or any participants in the ISO C++ standardization process, you agree to pay all legal expenses of said persons and/or entities and to indemnify every one of them in full in the event that any legally binding judgment is rendered against them.**

Intellectual property rights are important. You may not agree with every IP law and regulation out there (I certainly have some suggestions for reforming them), but we cannot ignore them and hope nobody notices. Many of us do things like develop software, do technical writing, or work for companies where that is a big part of what pays the bills. In other words, many people's livelihoods (including most, if not all, of ours) depend on laws governing intellectual property. So I apologize for all the scary language above. But until I go a decade without seeing statements like "I haven't decided on a license yet but here's some code I wrote", I'll continue to write scary statements in hopes of scaring people into taking intellectual property and the terms of the licenses under which such property is offered more seriously. And also because I really do mean them. I don't want to be facing $50,000+ in lawyers bills plus some large monetary judgment because someone passed off somebody else's code as their own or didn't follow their employer's policies or whatever. I don't expect that anyone else would want to be facing a situation such as that either.

I encourage anyone with intellectual property disputes to try to work them out reasonably first. Regardless, if you have any legal questions or concerns, including but not limited to intellectual property matters, you should contact a knowledgeable attorney.
