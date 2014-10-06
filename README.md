N4073 Reference Implementation
=============

Please read the [LICENSE](https://github.com/mikebmcl/N3888_RefImpl/blob/master/LICENSE.md) before cloning or forking the code as there is important information there!

Please see the [wiki](https://github.com/mikebmcl/N3888_RefImpl/wiki) for links to forks which provide alternate implementations!

Overview
-------------

This is a reference implementations of [N4073: A Proposal to Add 2D Rendering and Display to C++](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4073.pdf).

Requirements
-------------

For Windows platforms, it currently requires Visual Studio 2013 (the free Express for Windows Desktop version should suffice) and Windows Vista or newer.

For GNU/Linux platforms, it currently requires a non-ancient version of GNU autotools, cairo (>= 1.12.16), GTK+3.0 (>= 3.8.0), gmodule-2.0, gobject-2.0, and related libraries (autotools will tell you about any missing dependencies). By default it builds using GCC (>= 4.9.0), but you can configure it to use recent versions of Clang.

Discussion
-------------

There are several places to discuss this proposal. You can discuss it on the [std-proposals forum](https://groups.google.com/a/isocpp.org/forum/?fromgroups#!forum/std-proposals), on the [SG 13 forum](https://groups.google.com/a/isocpp.org/forum/?fromgroups#!forum/io), or you can leave a comment on the [the blog post announcing the proposal](http://isocpp.org/blog/2014/07/n4073). Members of the cairo graphics library community are, of course, welcome to discuss the proposal in the cairo mailing list as well if they would prefer that.

Feedback
-------------
If you have found a bug in the reference implementation or have a suggestion for improving N3888 please read the following. Note that any contributions must comply with the ISO patent and copyright policy, an overview of which is available in the ISO document [Participating in International Standardization](http://www.iso.org/iso/joining_in_2012.pdf).

* If you want to suggest a change to N4073 please file an [issue](https://github.com/mikebmcl/N3888_RefImpl/issues) with the tag [enhancement](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=enhancement&page=1&state=open). We will consider these for future revisions of N4073. Pull requests for suggested changes will not be accepted because this is a reference implementation.
* If you have found a bug in the reference implementation, please file an issue with the tag [bug](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=bug&page=1&state=open). Pull requests that fix bugs are welcome.
* If you have found any sort of error in N4073 (be it a typo, an omission, a contradiction, or some other non-subjective problem), please file an issue with the tag [proposal-bug](https://github.com/mikebmcl/N3888_RefImpl/issues?labels=proposal-bug&page=1&state=open). We will do our best to address these in the next revision of N4073.
* If you have created a reference implementation for another platform or tool-chain, please let us know. We welcome these types of pull requests provided that the implementation conforms to N4073 and the licensing terms are acceptable.

Subsequent revisions to N4073 will be maintained in branches or in separate repositories, depending on which strategy seems appropriate at that time.

Licenses and Contributions (Important!)
-------------

Any code that you offer as a pull request must be your own work. If your employer or institution has a moonlighting policy, the act of offering a pull request shall be considered a declaration that you complied with the terms of that policy and are free to make the contribution or that your employer or institution has expressly waived any IP rights it or they might have had in your contribution thus freeing you to make the contribution.

If your contribution makes use of third party libraries it must comply with the licensing terms of those libraries. If the library is licensed under multiple licenses you must indicate which license your contribution is using ("whichever" is not acceptable). The terms of those licenses must be compatible with the terms of the licenses of any existing code. Code licensed under any version of the GPL will not be considered. (Note: LGPL code will be considered, though licenses that give more freedom to other developers are preferred.)

You must specify a license for your contribution. If it is an original work, we suggest, but do not require, that you choose the MIT License. If the chosen license is unacceptable for some reason, you will be informed that the license is not acceptable.

If your code is a derivative work of the reference implementation it must be licensed under the terms of the MIT License unless you obtain an express, written waiver from the original author of the reference implementation, Michael B. McLaughlin. (Literally written, as in fixed on paper, signed, and physically mailed to you).

**If you fail to comply with the terms of any employer or institutional policies, the terms of any licenses, or if you infringe upon any patents, violate any trade secrets, violate any laws or regulations, or, by any act or omission, cause any legal action to be brought against the authors of N4073, the ISO C++ committee (ISO/IEC JTC1/SC22/WG21) or any of its members individually, or any participants in SG13 of the ISO C++ committee, you agree to pay all legal expenses of said persons and entities and indemnify every one of them in full in the event that any legally binding judgment is rendered against them.**

Intellectual property rights are important. You may not agree with every IP law and regulation out there (I certainly have some suggestions for reforming them), but we cannot ignore them and hope nobody notices. Many of us do things like develop software, do technical writing, or work for companies where that is a big part of what pays the bills. In other words, our livelihoods depend on copyrights and licenses and the such. So I apologize for all the scary language above. But until I go a decade without seeing statements like "I haven't decided on a license yet but here's some code I wrote", I'll continue to write scary statements in hopes of scaring people into taking copyrights and licenses more seriously. And because I really do mean them. I don't want to be facing $50,000+ in lawyers bills plus some large monetary judgment because someone passed off somebody else's code as their own or didn't follow their employer's policies or whatever. I don't know anyone else who'd want to be facing that either.

I encourage anyone with intellectual property disputes to try to work them out reasonably first, provided that doing so would not prejudice any of your rights in the event that a reasonable agreement cannot be reached. If you have any legal questions you should contact a knowledgeable attorney.
